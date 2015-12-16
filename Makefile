# Makefile 
#
# Luther Carroll
# 391929
# April 2015

OBJ     = main.o heap.o graph.o set.o dijkstra.o cover.o
CC      = g++
EXE     = assn2
CFLAGS  = -g -O2 #-m32 #-Wall

assn1:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) < testInput

main.o: cover.o Makefile
heap.o: heap.h
graph.o: graph.h
set.o: set.h
dijkstra.o: dijkstra.h heap.o set.o graph.o
cover.o: cover.h set.o
