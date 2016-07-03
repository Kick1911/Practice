#ifndef SUFFIX_ARRAY
#define SUFFIX_ARRAY

#define MAXLG 65536
#define MAXN 17

typedef struct suffix{
	int index;
	int rank[2];
}suffix_t;

void display_suffixes(suffix_t*, int);

int cmp(const void*, const void*);

int build_suffix_array(int*, char*, int);

#endif
