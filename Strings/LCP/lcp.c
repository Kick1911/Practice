#include <suffix_array.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

__inline__ int mod(int a, int b){
	int d = a/b;
	if( d < 1 ){
		int temp = b * d;
		return (b + (a - temp)) % b;
	}else{
		b *= d;
		return a - b;
	}
}

int lcp(int* arr, char* str, int len){
	int i, l, k, j;
	int suffix_array[len];
	int inv_suffix[len];
	build_suffix_array(suffix_array, str, len);
	i = 0; while( i < len ) printf("%d ",suffix_array[i++]);
	printf("\n");

	i = 0;while( i < len ){
		inv_suffix[suffix_array[i]] = i;
		i++;
	}

	i = 0;while( i < len ){
		l = 0;
		k = inv_suffix[i];
		j = suffix_array[k - 1];
		while( i + l < len && j + l < len && str[i + l] == str[j + l] ) l++;
		arr[k] = l;
		i++;
	}
	return 0;
}

int main(int argc, char** argv){
	int i;
	if( argc < 2 ) exit(1);
	char* str = argv[1];
	int lcp_array[strlen(str)];
	lcp(lcp_array, str, strlen(str));

	i = 0;while( i < strlen(str)){
		printf("%d ", lcp_array[i]);
		i++;
	}
	printf("\n");
	/* i = -20;while( i < 20 ){
		printf("%d : %d\n", i, mod(i,4));
		i++;
	} */
	return 0;
}
