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

    pid_t pointid;
    pointid = fork();    
    
    if (pointid == 0){ 
        struct timeval starttime;
        gettimeofday(&starttime, NULL);
        sprintf(ptr, "%lu", starttime.tv_usec);
        ptr += starttime.tv_usec;
        execvp(argv[1], &argv[1]);
        
    }
	else if (pointid < 0){ 
        return -1;

    }
    else {
        wait(NULL);
		struct timeval endtime;
        gettimeofday(&endtime, NULL);
        printf("Elapsed Time is %f seconds\n", (endtime.tv_usec - atof((char *)ptr)) / 100000); 
        shm_unlink(name);
    }
    return -1;
}