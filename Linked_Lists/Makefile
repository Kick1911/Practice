linkedlist: linkedlist.c linkedlist.h
	gcc -ansi linkedlist.c -I. -o linkedlist
compare_strings: linkedlist.h linkedlist.o compare_strings.c
	gcc -ansi compare_strings.c -I. -o compare_strings linkedlist.o 
linkedlist.o: linkedlist.h linkedlist.c
	gcc -ansi -c -I. linkedlist.c -o linkedlist.o
clean:
	rm -f linkedlist compare_strings linkedlist.o 
