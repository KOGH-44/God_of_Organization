app.out: main.o linkedList.o 
	gcc -o app.out linkedList.o main.o

main.o: main.c 
	gcc -c -o main.o main.c

linkedList.o: linkedList.h linkedList.c  	
	gcc -c -o linkedList.o linkedList.c	
