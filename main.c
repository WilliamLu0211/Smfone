#include "x.h"

char* get_last_entry(char* data){
  char* new_line = strstr(data, "\n");
  // printf("%s\n", new_line);
  if (*(new_line + 1))
    return get_last_entry(new_line + 1);
  else
    return data;
}

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
    return 1;
  }


  struct sembuf sf;
  sf.sem_op = -1;
  sf.sem_num = 0;
  sf.sem_flg = SEM_UNDO;
  semop(sem_id, &sf, 1);

  char* data = shmat(shm_id, 0, 0);
  if ( !strlen(data) )
    printf("Story is empty.\n");
  else {
    char* s = get_last_entry(data);
    char* t = malloc(strlen(s));
    strncpy(t, s, strlen(s) - 1);
    printf("Last Entry: [%s]\n", t);
  }

  printf("Please enter the next line: ");
  char new_line[256];
  scanf(" %[^\n]s", new_line);
  strcat(new_line, "\n");
  data = strcat(data, new_line);

  sf.sem_op = 1;
  semop(sem_id, &sf, 1);

  return 0;
}
