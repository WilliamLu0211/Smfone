#include "x.h"

int main(){
  // printf("#");

  int shm_id = shmget(SHM_KEY, SIZE, 0644);
  if (shm_id == -1){
    printf("Shared Memory Error %d: %s\n", errno, strerror(errno));
    return 1;
  }

  int sem_id = semget(SEM_KEY, 1, 0644);
  if (sem_id == -1){
    printf("Semaphore Error %d: %s\n", errno, strerror(errno));
    return 2;
  }


  struct sembuf sf;
  sf.sem_op = -1;
  sf.sem_num = 0;
  sf.sem_flg = SEM_UNDO;
  semop(sem_id, &sf, 1);

  char* last_entry = shmat(shm_id, 0, 0);
  printf("Last Entry: [%s]\n", last_entry);

  printf("Please enter the next line: ");
  char new_line[SIZE];
  scanf(" %[^\n]s", new_line);
  strcpy(last_entry, new_line);
  int fd = open(STORY, O_WRONLY | O_APPEND);
  if (fd == -1){
    printf("Error %d: %s\n", errno, strerror(errno));
    return 4;
  }
  strcat(new_line, "\n");
  write(fd, new_line, strlen(new_line));
  close(fd);

  sf.sem_op = 1;
  semop(sem_id, &sf, 1);

  return 0;
}
