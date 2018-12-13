#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* get_last_entry(char* data){
  char* follow;
  while (data){
    // printf("#");
    follow = data;
    // printf("%s", data);
    data = strstr(data, "\n");
    if (data)
      data ++;
  }
  return follow;
}

int main(){

  printf("%s", get_last_entry("ssssss\n"));

  return 0;
}
