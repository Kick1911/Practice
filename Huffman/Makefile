huff: Huffman.c linked.o
	gcc -g -O3 -ansi Huffman.c lib/linked.o -Iinclude/ -o huff
linked.o: linked_list.c
	gcc -O3 -ansi -c linked_list.c -Iinclude -o lib/linked.o
priority_queue:  priority_queue.c
	gcc $(CFLAG) -O3 -ansi priority_queue.c -Iinclude -o priority_queue
clean:
	rm huff lib/*.o
