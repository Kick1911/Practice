INCLUDE_PATH=../include
suffix_array: suffix_array.c
	gcc -ansi -O3 -I$(INCLUDE_PATH) suffix_array.c -o suffix_array
library: suffix_array.o
	gcc -ansi -shared -o ../lib/libstring.so.1 suffix_array.o
	cd ../lib && ln -s libstring.so.1 libstring.so
	cd - && rm -f suffix_array.o
suffix_array.o: suffix_array.c
	gcc -ansi -fPIC -c -Wall -I$(INCLUDE_PATH) suffix_array.c
clean:
	rm -f suffix_array suffix_array.o
