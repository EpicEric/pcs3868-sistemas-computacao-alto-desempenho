
all: soma-vetores-seq.o

soma-vetores-seq.o: soma-vetores-seq.c
	gcc -Wall -O4 -o $@ $<

run: soma-vetores-seq.o
	./$<

clean:
	rm -f *.o

time: soma-vetores-seq.o
	time ./$<

.PHONY: all run clean

