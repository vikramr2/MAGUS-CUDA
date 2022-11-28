batch-mafft: mafft.cu replaceu.o
	nvcc -o batch-mafft mafft.cu -lcudart -lcuda

replaceu.o: replaceu.cu io.o
	nvcc -o replaceu.o replaceu.cu io.o -lcudart -lcuda -c

io.o: io.cu mtxutl.cu
	nvcc -rdc=true io.cu mtxutl.cu

mtxutl.o: mtxutl.cu
	nvcc mtxutl.cu -o mtxutl.o -lcudart -lcuda -c

clean:
	rm batch-mafft
	rm io.o
	rm mtxutl.o
	rm replaceu.o