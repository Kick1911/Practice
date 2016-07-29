#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__inline__ int mod(int a, int b){
	int d = a/b;
	int r = a - b * d;
	
	if( d < 1 ){
		a = b + r;
		return a - b * (a / b);
	}else
		return r;
}

__inline__ double mod2(double a, double b){
	return a - b * floor(a / b);
}

int main(int argc, char** argv){
	printf("%d mod %d : %d\n", atoi(argv[1]), atoi(argv[2]), mod(atoi(argv[1]), atoi(argv[2])));
	printf("%.1f mod2 %.1f : %.1f\n", (double)atoi(argv[1]), (double)atoi(argv[2]), mod2((double)atoi(argv[1]), (double)atoi(argv[2])));
	/* int i = -20;while( i < 20 ){
		printf("%d : %d\n", i, mod(i,4));
		i++;
	} */
	return 0;
}
