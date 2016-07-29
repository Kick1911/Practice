#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20

struct graph{
	int V;
	int edge_grid[GRID_SIZE][GRID_SIZE];
};

void add_edge(struct graph g,int v,int e){
}

void traverse(int* graph[GRID_SIZE], int start, int V){
	int** ptr = graph;
	int temp, i;
	int stack[GRID_SIZE];
	int* checkpoint = stack;
	int visited[V];
	i = 0; while( i < V ) visited[i++] = 0;
	*checkpoint = start;
	visited[start] = 1;

	printf("%d ", start);
	i = 0; while( *stack != -1 ){
		temp = *checkpoint;
		while( ptr[temp][1] != -1 ){
			checkpoint++;
			if( !visited[ptr[temp][1]] ){
				printf("%d ", ptr[temp][1]);
				ptr[temp]++;
				temp = *ptr[temp];
				visited[temp] = 1;
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
	struct graph g;
	int V = 4;
	int* edge_grid[V];
	int i = 0; while( i < V )
		edge_grid[i++] =  malloc(sizeof(int) * V * 2);
	edge_grid[0][1] = 2;
	edge_grid[0][2] = 1;
	edge_grid[1][1] = 2;
	edge_grid[2][1] = 0;
	edge_grid[2][2] = 3;
	edge_grid[3][1] = 3;

	edge_grid[0][3] = -1;
	edge_grid[1][2] = -1;
	edge_grid[2][3] = -1;
	edge_grid[3][2] = -1;

	traverse(edge_grid, 2, V);
	return 0;
}
