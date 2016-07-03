#include <stdlib.h>
#include <string.h>
#include <suffix_array.h>


int cmp(const void* ptr_a, const void* ptr_b){
	suffix_t a = *((suffix_t*)ptr_a);
	suffix_t b = *((suffix_t*)ptr_b);
	return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1]) ? 0:1 :(a.rank[0] < b.rank[0]) ? 0:1;
}

int build_suffix_array(int* suffix_array, char* txt, int n){
	int i=0, k;
	suffix_t suffixes[n];
	while( i + 1 < n ){
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i] - 'a';
		suffixes[i].rank[1] = txt[i + 1] - 'a';
		i++;	
	}
	/* adding the last suffix */
	suffixes[i].index = i;
	suffixes[i].rank[0] = txt[i] - 'a';
	suffixes[i].rank[1] = -1;

	qsort(suffixes, n, sizeof(suffix_t), cmp);

	int ind[n];

	k = 4;
	while( k < 2*n ){
		int rank = 0;
		int prev_rank_0 = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		ind[suffixes[0].index] = 0;
		i = 1; while( i < n ){
			if( suffixes[i].rank[0] == prev_rank_0 && suffixes[i].rank[1] == suffixes[i - 1].rank[1] ){
				prev_rank_0 = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			}else{
				prev_rank_0 = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
			i++;
		}
		i = 0; while( i < n ){
			int next_index = suffixes[i].index + k/2;
			suffixes[i].rank[1] = (next_index < n)? suffixes[ind[next_index]].rank[0]: -1;
			i++;
		}
		qsort(suffixes, n, sizeof(suffix_t), cmp);
		k *= 2;
	}

	i = 0; while( i < n ){
		suffix_array[i] = suffixes[i].index;
		i++;
	}
	return 0;
}

/* int main(void){
	int result, len, i;
	char buf[100];
	result = scanf("%s",buf);
	if( !result ){ fprintf(stderr, "Error reading in the data: %d\n", result);exit(1); }
	len = strlen(buf);
	int suffix_array[len];
	build_suffix_array(suffix_array, buf, len);
	printf("SUFFIX ARRAY: ");
	i = 0; while( i < len )
		printf("%d ",suffix_array[i++]);
	printf("\n");
	return 0;
} */
