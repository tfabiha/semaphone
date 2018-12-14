#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#define STR_LEN 200

int main(){

    key_t key;
    key = ftok("makefile", 'a');

    printf("attempting to access file...\n");
    int sfd;
    sfd = semget(key, 1, 0);
    printf("sem val: %d\n", semctl(sfd, 0, GETVAL));
    struct sembuf buffer;
    //down the semaphore
    buffer.sem_op = -1;
    buffer.sem_num = 0;
    buffer.sem_flg = SEM_UNDO;
    semop(sfd, &buffer, 1);
    printf("sem val: %d\n", semctl(sfd, 0, GETVAL));

    //get last line of story
    int sgid;
    sgid = shmget(key, STR_LEN, 0);
    //return error if segment does not exist
    if (sgid == -1) {
        printf("shared memory error %d: %s\n", errno, strerror(errno));
    }

    else {
        char* curr_line = shmat(sgid, (void *) 0, 0);
        if (*curr_line) {
            printf("last entry: %s\n", curr_line);
        }
        else {
            printf("writing to a new story!\n");
        }

        printf("What do you want to add to the story?\n>");
        fgets(curr_line, STR_LEN, stdin);

        int fd = open("story", O_WRONLY | O_APPEND);
        if (fd == -1) {
            printf("file error %d: %s\n", errno, strerror(errno));
        }

        else {
            write(fd, curr_line, STR_LEN);
            close(fd);
            printf("new line has been added!\n");
        }

        //detach shared memory segment
        shmdt((void*) curr_line);
    }

    //up the semaphore
    buffer.sem_op = 1;
    semop(sfd, &buffer, 1);

    return 0;
}
