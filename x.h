#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

#define SHM_KEY 42690
#define SEM_KEY 48630
#define SIZE 1024

union semun{
  int val;
  struct semod_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

// struct sembuf{
//   short sem_op;
//   short sem_num;
//   short sem_flag;
// }
