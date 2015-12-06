#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(int *x,int *y){
	pid_t child_pid;
	child_pid = fork();
	if(child_pid != 0){
		while(++(*x) < 10)
			sleep(1);
		printf("x increment finished\n");
	}
	else{
		while(++(*y) < 10)
			sleep(1);
		printf("y increment finished\n");
	}
}

int main(){
	int x = 0, y = 0;
	printf("x: %d, y: %d\n", x, y);
	spawn(&x,&y);
	printf("x: %d, y: %d\n", x, y);

	return 0;
}
