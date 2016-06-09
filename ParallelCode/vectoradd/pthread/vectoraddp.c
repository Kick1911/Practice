#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct array_pair{
	int* array1;
	int* array2;
	int length;
}array_pair_t;

void* vectoradd_pthread(void* ptr){
	int* ptr1;
	int* ptr2;
	pthread_t thread;
	array_pair_t* array_pair_1 = (array_pair_t*)ptr;
	int i, fraction = array_pair_1->length / 2;
	if( array_pair_1->length <= 2 )
		return NULL;
	array_pair_1->length -= fraction;
	ptr1 = array_pair_1->array1;
	ptr2 = array_pair_1->array2;
	array_pair_1->array1 += array_pair_1->length;
	array_pair_1->array2 += array_pair_1->length;

	int result = pthread_create(&thread, NULL, vectoradd_pthread, (void*) ptr);
	if( result ){
		fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
		exit(EXIT_FAILURE);
	}

	i = 0;
	while( i < array_pair_1->length ){
		ptr1[i] += ptr2[i];
		i++;
	}

	pthread_join(thread, NULL);

}

int vectoradd(int* array1, int* array2, int length){
	array_pair_t array_pair_1 = {array1, array2, length};
	vectoradd_pthread((void*) &array_pair_1);
}

int main(int argc, char** argv){
	int array1[9] = {1,2,3,4,5,10,546,15,819};
	int array2[9] = {7,8,9,45,65,20,81,59,4};
	vectoradd(array1, array2, 10);
	int* ptr = array1;
	int* end = array1 + 9;
	while( ptr < end )
		printf("%d ",*ptr++);
	printf("\n");
	return 0;
}
