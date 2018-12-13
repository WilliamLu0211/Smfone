#include "x.h"

void create_memory(){

  int shm_id = shmget(SHM_KEY, SIZE, IPC_CREAT | IPC_EXCL | 0644);
  if (shm_id == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }

  int sem_id = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (sem_id == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }

  union semun sn;
  sn.val = 1;
  semctl(sem_id, 0, SETVAL, sn);
  printf("Shared memory and semaphore are created.\n");
}

void remove_memory(){

  int shm_id = shmget(SHM_KEY, SIZE, 0644);
  if (shm_id == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }

  int sem_id = semget(SEM_KEY, 1, 0644);
  if (sem_id == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }

  struct sembuf sf;
  sf.sem_op = -1;
  sf.sem_num = 0;
  sf.sem_flg = 0;
  semop(sem_id, &sf, 1);

  char* data = shmat(shm_id, 0, 0);
  printf("Removing Story: [%s]\n", data);
  shmctl(shm_id, IPC_RMID, 0);
  semctl(sem_id, 0, IPC_RMID);

}

void view_content(){

  int shm_id = shmget(SHM_KEY, SIZE, 0644);
  if (shm_id == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }

  char* data = shmat(shm_id, 0, 0);
  printf("Story Content: [%s]\n", data);

}

int main(int argc, char* argv[]){
  // printf("%d\n", argc);
  if (argc < 2)
    printf("Error: please give 1 argument.\n");
  else if ( !strcmp(argv[1], "-c") )
    create_memory();
  else if ( !strcmp(argv[1], "-r") )
    remove_memory();
  else if ( !strcmp(argv[1], "-v") )
    view_content();
  else
    printf("Error: invalid argument.\n");

  return 0;
}
