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

  int fd = open(STORY, O_CREAT | O_TRUNC, 0644);
  if (fd == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }
  // write(fd, "\0", 1);
  close(fd);
  printf("Story created.\n");
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

  // char* data = shmat(shm_id, 0, 0);

  int fd = open(STORY, O_RDONLY);
  if (fd == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }
  char *s = malloc(SIZE);
  read(fd, s, SIZE);
  close(fd);
  printf("Removing Story:\n%s", s);
  shmctl(shm_id, IPC_RMID, 0);
  semctl(sem_id, 0, IPC_RMID);
  char* args[] = {"rm", STORY, 0};
  execvp(args[0], args);
}

void view_content(){

  int fd = open(STORY, O_RDONLY);
  if (fd == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
  }
  char *s = malloc(SIZE);
  read(fd, s, SIZE);
  close(fd);
  printf("Story Content:\n%s", s);

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
