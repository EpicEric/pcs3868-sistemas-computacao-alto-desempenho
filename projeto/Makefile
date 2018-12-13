all: search-seq search

search-seq: *.h board.c graph.c heap.c state.c search-seq.c
	gcc -o search-seq board.c graph.c heap.c state.c search-seq.c

search: *.h board.c graph.c heap.c state.c search.c
	gcc -fopenmp -o search board.c graph.c heap.c state.c search.c

clean:
	rm -f search-seq search

.PHONY: all clean

