all: search-seq search

search-seq: board.h graph.h heap.h state.h board.c graph.c heap.c state.c search-seq.c
	gcc -o search-seq board.c graph.c heap.c state.c search-seq.c

search: board.h graph.h heap.h state.h board.c graph.c heap.c state.c search.c
	gcc -fopenmp -o search board.c graph.c heap.c state.c search.c

clean:
	rm -f search-seq search

.PHONY: all clean

