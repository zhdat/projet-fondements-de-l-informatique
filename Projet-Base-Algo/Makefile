CC       = gcc
RM       = rm
DOC      = doxygen
CPPFLAGS = -I./include
CFLAGS   = -Wall -Wextra -ansi -pedantic -g
LDFLAGS  = -L ./lib -limage64 # Add the libraries you will use, e.g. -lm

.PHONY: all doc clean distclean

all: ./bin/prog

./bin/prog: ./src/main.o ./src/fusion_iterative.o ./src/moment.o ./src/RAG.o # And others .o
	$(CC) $^ -o $@ $(LDFLAGS)

./src/main.o: ./src/main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

./src/fusion_iterative.o: ./src/fusion_iterative.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

# ./src/image.o: ./src/image.c
#	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c


./src/moment.o: ./src/moment.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

./src/RAG.o: ./src/RAG.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

doc:
	-@$(DOC) doc/Doxyfile

clean:
	-@$(RM) ./src/*.o

distclean: clean
	-@$(RM) ./bin/prog
