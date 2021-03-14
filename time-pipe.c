#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char *argv[]) {
	int fd[2];
	int status;
	struct timeval start;
	struct timeval end;
	
	pid_t pid;	
	//create pipe
	if (pipe(fd) < 0 || pipe(fd) < 0) {
		/* creating pipe failed */
		return 1;
	}

	pid = fork();
	if (pid == 0) {
		close(fd[READ_END]); //close unused end of pipe
		gettimeofday(&start, NULL);
		write(fd[1], &start, sizeof(struct timeval)); //write to pipe
		execvp(argv[1], &argv[1]);
        close(fd[WRITE_END]);
	} else if (pid < 0) {
		/* fork failed */
        return 1;
    } else {
		close(fd[WRITE_END]); //close unused end of pipe
		gettimeofday(&end, NULL);
		read(fd[READ_END], &start, sizeof(struct timeval)); //read from pipe
        printf("Time elapsed: %f seconds\n", (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec)/1000000); //calculate and print seconds
        close(fd[READ_END]);
	}
	return 0;
}