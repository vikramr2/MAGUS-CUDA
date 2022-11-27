batch-mafft: mafft.c replaceu.o
	gcc -o batch-mafft mafft.c

replaceu.o: replaceu.c io.o
	gcc -o replaceu.o replaceu.c io.o -c

io.o: io.c mtxutl.o
	gcc -o io.o io.c mtxutl.o -c

mtxutl.o: mtxutl.c
	gcc mtxutl.c -o mtxutl.o -c

clean:
	rm batch-mafft
	rm io.o
	rm mtxutl.o
	rm replaceu.o