CPPFLAGS=-lpthread

fork: temp_fork.c
	gcc -ansi temp_fork.c -o fork
temp: template.c
	gcc -ansi template.c -o temp $(CPPFLAGS)
qsort: quicksort.c
	gcc -ansi quicksort.c -o qsort
clean:
	rm temp fork
	cd sieve && $(MAKE) clean
	cd vectoradd && $(MAKE) clean
