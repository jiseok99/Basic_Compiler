#
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#

CC = gcc

CFLAGS =

OBJS = main.o util.o scan.o symtab.o analyze.o code.o cgen.o lex.yy.o


hw1_binary: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o hw1_binary

main.o: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

scan.o: scan.c scan.h util.h globals.h
	$(CC) $(CFLAGS) -c scan.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC) $(CFLAGS) -c analyze.c

code.o: code.c code.h globals.h
	$(CC) $(CFLAGS) -c code.c

cgen.o: cgen.c globals.h symtab.h code.h cgen.h
	$(CC) $(CFLAGS) -c cgen.c

lex.yy.c: lex/tiny.l
	flex lex/tiny.l

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c


clean:
	-rm $(OBJS)
	-rm lex.yy.c
	-rm hw1_binary
	-rm *.txt



tm.exe: tm.c
	$(CC) $(CFLAGS) -etm tm.c

tiny: tiny.exe

tm: tm.exe

all: tiny tm

