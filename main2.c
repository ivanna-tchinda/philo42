#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("seconds : %ld\nmicro seconds : %ld\nmilisecond: %ld\n", 
  current_time.tv_sec, current_time.tv_usec, (current_time.tv_usec)/1000);

  return 0;
}