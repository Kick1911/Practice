#include <suffix_array.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

__inline__ int mod(int a, int b){
	return a - b * (a/b);
}

int lcp(int* arr, char* str, int len){
	int i, l, k, j;
	int suffix_array[len];
	int inv_suffix[len];
	build_suffix_array(suffix_array, str, len);

	i = 0;while( i < len ){
		inv_suffix[suffix_array[i]] = i;
		i++;
	}
	i = 0;while( i < len ){
		l = 0;
		k = inv_suffix[i];
		j = suffix_array[mod((k-1), len)];
		while( str[i + l] == str[j + l] ) l++;
		arr[mod((k-1), len)] = l;
		i++;
	}
	return 0;
}

int main(void){
	char* str = "banana";
	int lcp_array[strlen(str)];
	lcp(lcp_array, str, strlen(str));
	return 0;
}
