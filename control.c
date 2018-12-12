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

int main(int argc, char * argv[])
{
  if (argc < 2)
    {
      printf("No flag detected\n");
      return 0;
    }

  if (strcmp(argv[1], "-c") == 0)
    {
      // make shared memory segemtn
      // create semaphore
      // open file with truncate
      printf("You put in a -c flag\n");
      return 0;
    } 

  if (strcmp(argv[1], "-r") == 0)
    {
      // remove shared memory
      // remove semaphore
      // display entire story
      // wait until semaphore is available
      printf("You put in a -r flag\n");
      return 0;
    }

  if (strcmp(argv[1], "-v") == 0)
    {
      // output the content of the story
      printf("You put in a -v flag\n");
      return 0;
    }
}
