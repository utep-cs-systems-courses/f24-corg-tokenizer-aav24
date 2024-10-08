# creating main makefile

# object files
OBJS= uimain.o src/tokenizer.o src/history.o

CFLAGS= -g -O3

all: main

main: $(OBJS)
	cc -o main $(CFLAGS) $(OBJS)

$(OBJS): src/tokenizer.h src/history.h

# cleans object files
clean:
	rm -f *.o src/*.o main


run:main
	./main
