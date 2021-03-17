#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int parent_fork[2];
	int child_fork[2];
	int curr;
	struct timeval starttime;
	struct timeval endtime;
	
	pid_t pointid;	
	curr = pipe(parent_fork);
	if (curr == -1) {
		return -1;
	}
	curr = pipe(child_fork);

	if (curr == -1) {
		return -1;
	}
    
	pointid = fork();
	if (pointid == 0) {
		gettimeofday(&starttime, NULL);
		write(parent_fork[1], &starttime, sizeof(struct timeval));
		execvp(argv[1], &argv[1]);
	} else {
		pid_t child = waitpid(pointid, &curr, 0);
		gettimeofday(&endtime, NULL);
		read(parent_fork[0], &starttime, sizeof(struct timeval));
		printf("Elapsed Time is %f\n", (double) (endtime.tv_sec - starttime.tv_sec)/1 + (double) (endtime.tv_usec - starttime.tv_usec)/1000000);
		
	}
	return 0;
}