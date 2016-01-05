huff: Huffman.c linked.o
	gcc -g -O3 -ansi Huffman.c lib/linked.o -Iinclude/ -o huff
linked.o: LinkedList.c
	gcc -O3 -ansi -c LinkedList.c -Iinclude -o lib/linked.o

clean:
	rm huff lib/*.o
