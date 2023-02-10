CC=gcc
CFLAGS=-c -Wall -O3
EXEC=hw2_binary

.SUFFIXES: .c .o

LEXCODE=lex/tiny.l
LEXSRC=tiny.lex.c

BISONCODE=yacc/tiny.y
BISONSRC=tiny.tab.c
BISONHDR=tiny.tab.h
BISONVERBOSE=tiny.output

SRCS=main.c util.c $(LEXSRC) $(BISONSRC)
OBJS=$(SRCS:.c=.o)

$(EXEC): $(LEXSRC) $(BISONSRC) $(OBJS)
	$(CC) -o $@ $(OBJS)

$(BISONSRC): $(LEXSRC) $(BISONCODE)
	bison -o $(BISONSRC) -vd $(BISONCODE)

$(LEXSRC): $(LEXCODE)
	flex -o $(LEXSRC) $(LEXCODE)

clean:
	rm -f $(OBJS) 
	rm -f $(EXEC) 
	rm -f $(LEXSRC) 
	rm -f $(BISONSRC) 
	rm -f $(BISONHDR) 
	rm -f $(BISONVERBOSE)
	rm *.txt
