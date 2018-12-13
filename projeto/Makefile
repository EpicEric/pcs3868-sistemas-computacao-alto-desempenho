# all: search-seq search
all: search

search-seq: *.h board.c graph.c heap.c state.c search-seq.c
	gcc -o search-seq *.c

search: *.h board.c graph.c heap.c state.c search.c
	gcc -fopenmp -o search *.c

clean:
	rm -f search-seq search

.PHONY: all clean

