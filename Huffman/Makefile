LIB = lib
CFLAG = -g -O0 -ansi
LFLAG = -O0 -ansi -c -g
INCLUDE = -Iinclude

huff: Huffman.c $(LIB)/libhuff.a $(LIB)/libhash.so
	gcc $(CFLAG) -o huff Huffman.c -Llib $(INCLUDE) -lhuff -lhash
$(LIB)/libhash.so: Hash_Table/hash_table.c Hash_Table/hash_table.h
	cd Hash_Table; $(MAKE) library
$(LIB)/libhuff.a: $(LIB)/linked_list.o $(LIB)/priority_queue.o
	cd lib; ar -cvq libhuff.a *.o
$(LIB)/linked_list.o: linked_list.c
	gcc $(LFLAG) linked_list.c $(INCLUDE) -o $(LIB)/linked_list.o
$(LIB)/priority_queue.o:  priority_queue.c
	gcc $(LFLAG) priority_queue.c $(INCLUDE) -o $(LIB)/priority_queue.o
test: test.c
	gcc $(CFLAG) test.c -Llib -lhuff $(INCLUDE) -o test
clean:
	rm -f compressed.huff huff test a.out $(LIB)/*.[a,so.1]
	cd Hash_Table; $(MAKE) clean
