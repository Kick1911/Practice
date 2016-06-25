LIB = lib
CFLAG = -g -O3 -ansi
LFLAG = -O3 -ansi -c -g
INCLUDE = -Iinclude

huff: Huffman.c libhuff.a
	gcc $(CFLAG) Huffman.c -Llib -lhuff $(INCLUDE) -o huff
libhuff.a: linked_list.o priority_queue.o
	cd lib; ar -cvq libhuff.a *.o
linked_list.o: linked_list.c
	gcc $(LFLAG) linked_list.c $(INCLUDE) -o $(LIB)/linked_list.o
priority_queue.o:  priority_queue.c
	gcc $(LFLAG) priority_queue.c $(INCLUDE) -o $(LIB)/priority_queue.o
test: test.c
	gcc $(CFLAG) test.c -Llib -lhuff $(INCLUDE) -o test
clean:
	rm -f compressed.huff huff test a.out $(LIB)/*
