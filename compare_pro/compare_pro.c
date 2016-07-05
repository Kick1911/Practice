#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	int i;
	char* ptr;
	char* str = "word";
	char** progs = argv + 1;
	/* i = 0; while( i < argc - 1 ){ */
		char buffer[50];
		*buffer = '.';
		buffer[1] = '/';
		ptr = buffer + 2;

		int l = strlen(argv[1]);
		int l_2 = strlen(str);
		memcpy(ptr, argv[1], l + 1);
		ptr[l] = ' ';
		memcpy(ptr + l + 1, str, l_2 + 1);
		ptr[l + l_2 + 1] = 0;
		printf("%s\n",buffer);
	return 0;
}
