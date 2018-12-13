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

// union semun {
//     int     val;            /* value for SETVAL */
//     struct  semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
//     u_short *array;         /* array for GETALL & SETALL */
// };

int main(int argc, char * argv[])
{
    key_t key;
    key = ftok("makefile", 'a');

  if (argc < 2)
    {
      printf("No flag detected\n");
      return 0;
    }

  if (strcmp(argv[1], "-c") == 0)
    {
      // make shared memory segment
      // create semaphore
      // open file with truncate
      printf("You put in a -c flag\n");
      int sgid;

      //make shared memory segment
      sgid = shmget(key, STR_LEN, 0644 | IPC_CREAT);
      //return error if segment already exists
      if (sgid == -1) {
          printf("segment error %d: %s\n", errno, strerror(errno));
      }

      //create semaphore
      int sfd;
      sfd = semget(key, 1, IPC_CREAT | IPC_EXCL);

      if (sfd == -1) {
          printf("semaphore error %d: %s\n", errno, strerror(errno));
      }

      //sets value of semaphore
      union semun data;
      data.val = 1;
      semctl(sfd, 0, SETVAL, data);

      //open file with truncate
      int fd;
      fd = open("story", O_CREAT | O_EXCL);
      if (fd == -1) {
          fd = open("story", O_TRUNC);
      }
      close(fd);

      return 0;
    }

  if (strcmp(argv[1], "-r") == 0)
    {
      // remove shared memory
      // remove semaphore
      // display entire story
      // wait until semaphore is available
      printf("You put in a -r flag\n");

      //remove shared memory
      sgid = shmget(key, STR_LEN,);
      //return error if segment already exists
      if (sgid == -1) {
          printf("segment error %d: %s\n", errno, strerror(errno));
      }
      shmctl(sgid, IPC_RMID, NULL);
      //remove semaphore
      int sfd;
      sfd = semget(key, 1, 0);
      struct sembuf buffer;
      buffer.sem_op = -1;
      buffer.sem_num = 0;
      buffer.sem_flg = SEM_UNDO;
      semop(sfd, &buffer, 1);
      semctl(sfd, 0, IPC_RMID);

      //display content of story

      return 0;
    }

  if (strcmp(argv[1], "-v") == 0)
    {
      // output the content of the story
      printf("You put in a -v flag\n");
      return 0;
    }
}
