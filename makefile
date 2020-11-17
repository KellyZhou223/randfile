all: main.o
	gcc -o randfile main.c

main.o: main.c
	gcc -c main.c

run:
	./randfile

clean:
	rm *.o
	rm output.out
	rm randfile.exe
