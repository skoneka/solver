/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  punkt wejściowy programu
 *
 *        Version:  1.0
 *        Created:  16.01.2010 21:15:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "define.h"
#include "tester.h"
#include "man_tester.xxd"

int setup_arguments(int argc, char **argv);
void show_description(FILE *f);
void show_options(FILE *f);
void show_help(FILE *f);


struct globalArgs gArgs;

static struct option long_options[] = {
    /* These options set a flag. */
    {"verbose", no_argument, &gArgs.verbose, 'v'},
    {"quiet", no_argument, &gArgs.silent, 'q'},
    {"auto", no_argument, &gArgs.matrix_auto, 'a'},
    {"nice", no_argument, &gArgs.nice_matrix, 'n'},
    {"help", no_argument, &gArgs.show_help, 'h'},
    {"static", no_argument, &gArgs.m_static, 't'},
    /* These options don't set a flag.
     We distinguish them by their indices. */
    {"size", required_argument, 0, 's'},
    {"sparsity", required_argument, 0, 'r'},
    {"file", required_argument, 0, 'o'},
    {"m", required_argument, 0, 'm'},
    {"mx" , required_argument, 0 ,'x'},
    {"mx0" , required_argument, 0 ,'0'},
    {"max" , required_argument, 0 ,'y'},
    {"min" , required_argument, 0 ,'z'},
    {"check", required_argument, 0, 'c'},
    {"diagonal", required_argument, 0, 'd'},
    
    {"precision", required_argument, 0, 'p'},
    {"max-iter", required_argument, 0, 'i'},
    {0, 0, 0, 0}
};

    int
main (argc, argv)
     int argc;
     char **argv;
{
    int ret = EXIT_SUCCESS;

    show_description(stdout);

    if(argc<2) {
        show_help(stdout);
        return EXIT_SUCCESS;
    }
    else if(setup_arguments(argc,argv))
        return EXIT_FAILURE;

    fprintf(stderr,"Tester: setting up\n");
    if(tester_setup(&gArgs)) {
        fprintf(stderr,"Tester: ERROR - invalid arguments\n");
        ret = EXIT_FAILURE;
    }
    else {
        fprintf(stderr,"Tester: running\n");
        if(tester_run()) {
            fprintf(stderr, "Tester: ERROR - solver failed during computations");
            ret = EXIT_FAILURE;
        }
    }

    fprintf(stderr,"Tester: cleaning up\n");
    tester_finish();

    return ret;
}

void show_description(FILE *f)
{
    fprintf(f,"Iteracyjny solver do rzadkich układów równań.\t"
            "by Artur Skonecki\n");
}


void show_options(FILE *f)
{
    int index=0;
    fprintf(f,"options:\n");
    while(long_options[index].name) {
        fprintf(f," -%c --%s;",long_options[index].val,long_options[index].name);
        index++;
    }
    fprintf(f,"\n");
}

void show_help(FILE *f)
{
    fprintf(f,man_tester);
    /* show_options(f); */
}

int 
setup_arguments(int argc, char **argv)
{

    int c;

    gArgs.verbose = FALSE;
    gArgs.silent = FALSE;
    gArgs.matrix_auto=FALSE;
    gArgs.nice_matrix=FALSE;
    gArgs.m_static = FALSE;
    gArgs.range_max=10;
    gArgs.outFile=NULL;
    gArgs.matrix=NULL;
    gArgs.matrix_x=NULL;
    gArgs.matrix_x0=NULL;
    gArgs.m_size=10;
    gArgs.m_sparsity=0.1;
    gArgs.max_iter=0;
    gArgs.range_min=-10;
    gArgs.check=0.1;
    gArgs.precision=1e-10;
    gArgs.diagonal=1.0;

    while (1) {

	/* getopt_long stores the option index here. */
	int option_index = 0;

	c = getopt_long (argc, argv, "vahqngtc:d:0:x:f:m:p:i:s:r:o:y:z:",
			 long_options, &option_index);

	/* Detect the end of the options. */
	if (c == -1)
	    break;
/*     if(gArgs.verbose) {
	    fprintf (stderr,", option %s", long_options[option_index].name);
	    if (optarg)
		fprintf(stderr," with \"arg\" %s", optarg);
	    fprintf(stderr,"\n");
    } */
	switch (c) {
	case 0:
	    /* If this option set a flag, do nothing else now. */
	    /* if (long_options[option_index].flag != 0)
		break; */

	    break;
    case 's':
        gArgs.m_size=atoi(optarg);
        break;
    case 'r':
        gArgs.m_sparsity=atof(optarg);
        break;
	case 'v':
        gArgs.verbose=TRUE;
	    break;	
    case 'q':
        gArgs.silent=TRUE;
	    break;
    case 'c':
        gArgs.check=atof(optarg);
        break;
	case 'a':
        gArgs.matrix_auto=TRUE;
	    break;
    case 'p':
        gArgs.precision=atof(optarg);
        break;
    case 'i':
        gArgs.max_iter=atoi(optarg);
        break;
	case 'd':
        gArgs.diagonal=atof(optarg);
	    break;
    case 'y':
        gArgs.range_min=atof(optarg);
        break; 
    case 'z':
        gArgs.range_max=atof(optarg);
        break;
	case 'n':
        gArgs.nice_matrix=TRUE;
	    break;
	case 'o':
        gArgs.outFile=optarg;
        break;
	case 'm':
	    gArgs.matrix = optarg;
	    break;
	case 'x':
	    gArgs.matrix_x = optarg;
	    break;	
    case 't':
	    gArgs.m_static = TRUE;
	    break;
    case '0':
	    gArgs.matrix_x0 = optarg;
	    break;
    case 'h':
        gArgs.show_help=TRUE;
        break;
	case '?':
        fprintf(stderr,"Aborting..\n");
        return 1;
	    /* getopt_long already printed an error message. */
	    break;

	default:
	    abort ();
	}
    }
    fprintf(stderr,"\n");
    if(gArgs.show_help) {
        show_help(stderr);
        return 1;
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
	fprintf (stderr,"non-option ARGV-elements: ");
	while (optind < argc)
	    fprintf (stderr,"%s ", argv[optind++]);
	fprintf(stderr,"\n");
    fprintf(stderr,"Aborting..\n");
    return 1;
    }
    
    return 0;
}
