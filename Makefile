all: doubleLinkedList

doubleLinkedList: doubleLinkedList.o
	gcc -o doubleLinkedList doubleLinkedList.o

doubleLinkedList.o: doubleLinkedList.c
	gcc -c doubleLinkedList.c

queue: queue.o
	gcc -o queue queue.o

queue.o: queue.c
	gcc -c queue.c

clean:
	rm -rf doubleLinkedList queue
	rm -rf *.o
