#include <stdio.h>
#include <stdlib.h>

typedef struct graph{
	int V;
	int** grid;
} graph_t;

int add_connect(graph_t g, int from, int to){
	int** ptr = g.grid;
	while( *ptr[from] || *ptr[from] == 0 ) ptr[from]++;
	*ptr[from] = to;
}

void traverse(graph_t g, int start){
	int** ptr = g.grid;
	int V = g.V;
	int temp, i;
	int stack[V];
	int* checkpoint = stack;
	int visited[V];
	i = 0; while( i < V ) visited[i++] = 0;
	*checkpoint = start;
	visited[start] = 1;

	printf("%d ", start);
	i = 0; while( *stack != -1 ){
		temp = *checkpoint;
		while( *ptr[temp] != -1 ){
			if( !visited[*ptr[temp]] ){
				printf("%d ", *ptr[temp]);
				ptr[temp]++;
				temp = ptr[temp][-1];
				visited[temp] = 1;
				checkpoint++;
				*checkpoint = temp;
			}else
				ptr[temp]++;
		}
		*checkpoint = -1;
		checkpoint--;
	}
	printf("\n");
}

int main(int argc,char** argv){
	int V = 4;
	int* edge_grid[V];
	int i = 0; while( i < V )
		edge_grid[i++] =  malloc(sizeof(int) * V);
	edge_grid[0][0] = 2;
	edge_grid[0][1] = 1;
	edge_grid[1][0] = 2;
	edge_grid[2][0] = 0;
	edge_grid[2][1] = 3;
	edge_grid[3][0] = 3;

	edge_grid[0][2] = -1;
	edge_grid[1][1] = -1;
	edge_grid[2][2] = -1;
	edge_grid[3][1] = -1;

	graph_t g;
	g.V = V;
	g.grid = edge_grid;

	traverse(g, 2);
	return 0;
}
