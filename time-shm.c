#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h> 
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    const int SIZE = 4096;
    const char *name = "OS";
    int fd;
    char *ptr;


    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 

    close(fd);

    pid_t pid;
    pid = fork();    
    
    if (pid < 0){ 
        return 0;
    }
	else if (pid == 0){ 
	    struct timeval start;
        gettimeofday(&start, NULL);
        sprintf(ptr, "%lu", start.tv_usec);
        ptr += start.tv_usec;
        execvp(argv[1], &argv[1]);

    }
    else {
        wait(NULL);
		struct timeval end;
        gettimeofday(&end, NULL);
        printf("Elapsed Time: %f seconds\n", (end.tv_usec - atof((char *)ptr)) / 100000); 
        shm_unlink(name);
    }
    return 0;
}