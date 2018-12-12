#include "x.h"

void create(){

  int shm_id = shmget(SHM_KEY, SIZE, IPC_CREAT | 0644);
  if (shm_id == -1){
    printf("Error %d: %s", errno, strerror(errno));
    return;
  }
  
  int sem_id = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (sem_id == -1){
    printf("Error %d: %s", errno, strerror(errno));
    return;
  }

  union semum s;
  s.val = 1;
  semctl(sem_id, 0, SETVAL, s);

}

void remove(){

  
}

int main(int argc, char* argv[]){

  if (!argc)
    printf("Error: please give 1 argument.\n");
  else if ( !strcmp(argv[0], "-c") )
    create();
  else if ( !strcmp(argv[0], "-r") )
    remove();
  else if ( !strcmp(argv[0], "-v") )
    view();
  else
    printf("Error: invalid argument.\n");
  
  return 0;
}
