INCLUDE_PATH=../include
LIB_PATH=../lib
lcp: lcp.c
	gcc -ansi -I$(INCLUDE_PATH) -L$(LIB_PATH) -lstring lcp.c -o lcp
helsinki_lcp: helsinki_lcp.c
	gcc -ansi -I$(INCLUDE_PATH) -L$(LIB_PATH) -lstring helsinki_lcp.c -o helsinki_lcp
working_lcp: working_lcp.cpp
	g++ working_lcp.cpp -o working_lcp
clean:
	rm -f lcp working_lcp helsinki_lcp *.out
