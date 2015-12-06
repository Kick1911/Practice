#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(int*,int*);

int isSorted(int *array){
	while(*(array + 1) ){
		if( *array > *(array + 1) )
			return -1;
		array++;
	}
	return 0;
}

int readin(char* filename,int * array){
	int num;
	FILE* f = fopen(filename,"r");
	int result = fscanf(f,"%d",&num);
	while( result != EOF ){
		*array++ = num;
		result = fscanf(f,"%d",&num);
	}
	*array = '\0';
}

void swap(int* i, int* j){
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

void display(int * start,int* end){
	printf("[ ");
	while(start != end + 1)
		printf("%d ",*start++);
	printf("]\n");
}

int* pointlast(int* array){
	while(*(array + 1)){array++;}
	return array;
}

void quicksort(int *array){
	int* end = pointlast(array);
	sort(array,end);
}

int* partition(int* start,int* end){
	int pivot = *start;
	int *i = start, *j = end + 1;

	while( i < j ){
		while( i < j-1 && pivot >= *(++i) ){}
		while( i < j && pivot < *(--j) ){}

		if( i < j )
			swap(i,j);
	}
	if( pivot < *i ){
		swap(start,i-1);
		return i-1;
	}
	else{
		swap(start,i);
		return i;
	}
}

void sort(int *start,int *end){
	/* display(start,end); */
	if( end == start ) return;
	if( start + 1 == end ){
		if( *start > *end ){
			swap(start,end);
			return;
		}
		else
			return;
	}
	int* ptr = partition(start,end);
	/* display(start,end); */
	if( ptr != start )
		sort(start,ptr-1);
	if( ptr != end )
		sort(ptr+1,end);
}

int main(int argc, char** argv){
	/* int array[5] = { 48,54,47,47,58 }; */
	int *array =  malloc( sizeof(int) * 10000000 );

	readin("array.data", array);
	/* printf("First: %d, Last: %d\n",*array, *pointlast(array) ); */
	/* printf("%d\n",*partition(array,array + 4 ) ); */
	quicksort(array);
	/* printf("First: %d, Last: %d\n",*array, *pointlast(array) ); */
	/* display(array, pointlast(array)); */
	/* printf("The array %s sorted\n", ((!isSorted(array))?"is":"is not") ); */
	free(array);
}
