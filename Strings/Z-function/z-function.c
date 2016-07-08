#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__inline__ int min(int n1, int n2){
	return (n1 < n2)? n1 : n2;
}

int z_function(int* z, char* s, int n){
	int i, l = 0, r = 0;
	i = 0; while( i < n) z[i++] = 0;
	i = 1; while (i < n) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
		i++;
	}
	return 0;
}

int main(){
	int t, i, j, n;
	scanf("%d",&t);
	char a[100001];
	i = 0;while( i < t ){
		scanf("%s", a);
		n = strlen(a);
		int z[n];
		z_function(z, a, n);
		j = 0; while( j < n)
			printf("%d ",z[j++]);
		printf("\n");
		i++;
	}
	return 0;
}
