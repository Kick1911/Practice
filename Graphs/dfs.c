#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20
int V = 5;

struct graph{
	int edge_grid[GRID_SIZE][GRID_SIZE]; 
};

void add_edge(struct graph g,int v,int e){
	int i=0;
	while(!g.edge_grid[v][i])
	i++;
	if( i == GRID_SIZE ){
		fprintf(stderr,"Vertice cannot take anymore edges.");
		exit(2);
	}
	g.edge_grid[v][i] = e;
}

void DFSUtil(struct graph g, int* ptr, int visited[]){
	visited[v] = 1;
	printf("%d ",v);

	g.edge_grid[v] = *(g.edge_grid + v) + 1;  /* Code Like a C programmer!!! pls! */
	int i = *(g.edge_grid[v]);
	while( i ){
		printf("%d",i);
		if(!visited[i])
			DFSUtil(g, i,visited);
	}
}

void DFS(struct graph g, int* ptr){
	int i=0;
	int visited[V];
	while( i < V )
		visited[i++] = 0;

	DFSUtil(g, ptr, visited);
}

int main(int argc,char** argv){
	struct graph g;
	g.edge_grid[1][1] = 2;
	g.edge_grid[1][2] = 3;
	g.edge_grid[2][1] = 3;
	g.edge_grid[3][1] = 1;
	g.edge_grid[3][2] = 4;
	g.edge_grid[4][1] = 4;

	int* ptr = g.edge_grid[3];
	DFS(g,ptr);
	return 0;
}
