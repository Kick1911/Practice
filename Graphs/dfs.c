#include <stdio.h>
#include <stdlib.h>

int GRID_SIZE = 20;
int V = 5;

struct graph{
	int edge_grid[GRID_SIZE][GRID_SIZE]; 
}

void add_edge(struct graph g,int v,int e){
	int i=0;
	while(!g.edge_grid[v][i])
		i++;
	if( i == GRID_SIZE ){
		fprintf("Vertice cannot take anymore edges.");
		exit(2);
	}
	g.edge_grid[v][i] = e;
}

void DFSUtil(struct graph g, int v, int visited[]){
	visited[v] = true;
	printf("%d ",v);

	int i = g.edge_grid[v][0];
	while( i )
		if(!visited[i])
			DFSUtil(g, i,visited);
}

void DFS(struct graph g, int v){
	int i=0;
	int visited[V];
	while( i < V )
		visited[i++] = 0;

	DFSUtil(g, v, visited);
}

int main(int argc,char** argv){
	struct graph g;
	return 0;
}
