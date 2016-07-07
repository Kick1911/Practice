#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 /* The correct way to inplement concate */
char* my_strcat(char* dest, const char* source){
	while( (*dest++ = *source++) != '\0' );
	return dest - 1;
}

char* rand_word(char* ptr, int n){
	int i = 0;
	while( i < n )
		ptr[i++] = (char) ( rand() % ('F' - 'A' - 1) ) + 'A';
	ptr[i] = 0;
	return ptr + i;
}

char* str_array_cat(char* str, char** arr, char seperator, int n){
	int i = 0;
	char* ptr;
	ptr = my_strcat(str, *arr++);
	i++;
	while( i < n ){
		*ptr++ = seperator;
		ptr = my_strcat(ptr, *arr++);
		i++;
	}
	*ptr = 0;
	return ptr;
}

int test_progs(int argc, char** argv, unsigned int seed){
	int i, err_code;
	char* buffer = (char*)malloc(100), *test = (char*)malloc(50);
	char* diff = "diff ";
	char diff_command[50];
	char* ptr, *test_ptr;
	char* test_files[2];
	char** progs = argv + 1;
	i = 0; while( i < argc - 1 ){
		srand(seed);
		*buffer = '.';
		buffer[1] = '/';
		ptr = buffer + 2;
		ptr = my_strcat(ptr, progs[i]);
		*ptr++ = ' ';
		int random = (rand() % 10) + 5;
		ptr = rand_word(ptr, random);
		test_ptr = my_strcat(my_strcat(test, progs[i]), ".out" );
		*test_ptr = 0;
		ptr = my_strcat(ptr, " > ");
		ptr = my_strcat(ptr, test);
		*ptr = 0;
		test_files[i] = (char*)malloc(50);
		strcpy(test_files[i], test);
		err_code = system(buffer);
		printf("%s\n", buffer);
		if( err_code ){
			printf("Program: \'%s\' failed on seed: %d\n", progs[i], seed);
			exit(2);
		}
		i++;
	}
	ptr = my_strcat(diff_command, "diff ");
	str_array_cat(ptr, test_files, ' ', 2);
	err_code = system(diff_command);
	if( err_code ){
		printf("Outputs differ on seed %d\n", seed);
		exit(2);
	}else
		printf("Success\n");
	return 0;
}

int main(int argc, char** argv){
	unsigned int i = 1, bound = 1 << 31;
	while( i <= bound )
		test_progs(argc, argv, i++);
	return 0;
}
