app.out: main.o linkedList.o
	gcc -o app.out main.c linkedList.c 

main.o: main.c 
	gcc -c -o main.o main.c

linkedList.o: linkedList.h linkedList.c
	gcc -c -o linkedList.o linkedList.c