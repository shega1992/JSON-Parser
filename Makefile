json: parser.o scanner.o main.o 
	gcc -o json main.o scanner.o parser.o 

parser.o: parser.c 
	gcc -c parser.c -o parser.o

scanner.o: scanner.c
	gcc -c scanner.c -o scanner.o

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm -f scanner.o json parser.o *.o scan
