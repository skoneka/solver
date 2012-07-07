OBJS = $(DSRC)/solver.o $(DSRC)/yale.o $(DSRC)/matrix.o $(DSRC)/vec.o $(DSRC)/tester.o
SRCS = $(OBJS:.o=.c)
HEADERS= $(OBJS:.o=.h) $(DSRC)/define.h
MAIN= $(DSRC)/main.o
MAINSRC= $(MAIN:.o=.c)
MAIN1 = $(DSRC)/test2.o
MAIN2 = $(DSRC)/tYale.c

RDIR=release
DDATA=data
DBIN=bin
DSRC=src
DDOC=doc


#DEBUG += -ggdb 
DEBUG += -DDBG_SOLVER
#DEBUG += -DMATLAB
#DEBUG += -DDEBUG

CC=gcc
DLIBS= -lefence
LIBS=-lm #$(DLIBS)
CFLAGS = $(DEBUG) -Wall  -std=c89 -pedantic
LFLAGS = $(DEBUG) -Wall $(LIBS)
prog = solver
prog1 = test2
prog3 = test
prog2 = tyale

INDENT= indent -br -i 4 --no-tabs 

all: $(prog)

-include MakeSupport

release: $(prog)
	rm -rf $(RDIR)
	mkdir $(RDIR)
	cp README $(RDIR)
	cp Makefile $(RDIR)

	mkdir $(RDIR)/$(DSRC)
	cp $(SRCS) $(HEADERS) $(MAINSRC) $(DSRC)/man_tester.xxd $(RDIR)/$(DSRC)

	
	mkdir $(RDIR)/$(DDATA)
	cp $(DDATA)/* $(RDIR)/$(DDATA)
	
	mkdir $(RDIR)/$(DDOC)
	cp $(DDOC)/diagram_implement.xmi $(RDIR)/$(DDOC)
	cp $(DDOC)/solver.tex $(RDIR)/$(DDOC)
	cp $(DDOC)/solver.pdf $(RDIR)/$(DDOC)
	cp $(DDOC)/diagram_implement.pdf $(RDIR)/$(DDOC)
	cp $(DDOC)/man_tester $(RDIR)/$(DDOC)
	cp $(DDOC)/man_solve $(RDIR)/$(DDOC)
	cp $(DDOC)/man_solve $(RDIR)/$(DDOC)
	cp $(DDOC)/make $(RDIR)/$(DDOC)
	
	mkdir $(RDIR)/$(DBIN)

	$(INDENT) $(RDIR)/$(SRCS) $(RDIR)/$(HEADERS)
	rm $(RDIR)/$(DSRC)/*.h~ $(RDIR)/$(DSRC)/*.c~
	tar cjvf $(RDIR).tar.bz2 $(RDIR)

$(prog): $(MAIN) $(OBJS) src/man_tester.xxd
	$(CC) $(LFLAGS) $(OBJS) $(MAIN) -o  $(DBIN)/$(prog) 
	ln -sf $(DBIN)/$(prog) ./solver

debug: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(prog)

$(prog1): $(MAIN1) $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(MAIN1) -o $(prog1)

$(prog2): $(MAIN2) $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(MAIN2) -o $(prog2)
depend:
	rm -f MakeSupport
	echo $(SRCS) $(MAINSRC)|tr -s " " "\n" |while read i; do echo $(DSRC)/|tr -d "\n" >> MakeSupport;  gcc -M $$i >> MakeSupport; done

indent:
	$(INDENT) $(SRCS) $(HEADERS)
cleano:
	rm -f $(DSRC)/*.o

cleanmeta:
	rm -f $(DSRC)/*~ $(DSRC)/.*.swp $(DSRC)/.*.swo

clean: cleano
	\rm $(prog)
	rm $(DBIN)/$(prog)

doc:
	sh -c "cd doc; ./make"

cleanall: clean cleanmeta
c: clean
ca: cleanall
cm: cleanmeta


.PHONY: all
.PHONY: clean cleanmeta cleanall indent cleano doc release
.PHONY: depend
