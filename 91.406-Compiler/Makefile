CC=gcc
CFLAGS=-g
OBJECTS=y.tab.o lex.yy.o frontend.o tacend.o expression.o symbollist.o type.o stack.o main.o tac.o symbol.o symboltable.o utilities.o codegen.o regdesc.o
YACCFLAGS=-t #-v

all: $(OBJECTS)
	$(CC) -o main $(OBJECTS)

tacend.o: tacend.h tacend.c
	$(CC) -c $(CFLAGS) tacend.c

frontend.o: frontend.h frontend.c
	$(CC) -c $(CFLAGS) frontend.c

stack.o: stack.h stack.c
	$(CC) -c $(CFLAGS) stack.c

symbollist.o: symbollist.h symbollist.c
	$(CC) -c $(CFLAGS) symbollist.c

codegen.o: codegen.h codegen.c
	$(CC) -c $(CFLAGS) codegen.c

type.o: type.h type.c
	$(CC) -c $(CFLAGS) type.c

expression.o: expression.h expression.c
	$(CC) -c $(CFLAGS) expression.c

regdesc.o : regdesc.h regdesc.c
	$(CC) -c $(CFLAGS) regdesc.c

tac.o: tac.h tac.c
	$(CC) -c $(CFLAGS) tac.c

utlities.o: utilities.h utilities.c
	$(CC) -c $(CFLAGS) utilities.c

symboltable.o: symboltable.h symboltable.c
	$(CC) -c $(CFLAGS) symboltable.c

main.o: main.c main.h
	$(CC) -c $(CFLAGS) main.c

y.tab.o: pascal.y
	yacc -d $(YACCFLAGS) pascal.y
	$(CC) -c $(CFLAGS) y.tab.c

lex.yy.o: pascal.l
	lex pascal.l
	$(CC) -c $(CFLAGS) lex.yy.c

symbol.o: symbol.h symbol.c
	$(CC) -c $(CFLAGS) symbol.c

clean:
	rm -f y.tab.h
	rm -f y.tab.c
	rm -f lex.yy.c
	rm -f *.o
	rm -f *~
	rm -f *#
	rm -f *.gch
