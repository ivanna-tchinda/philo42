#include "philo_bonus.h"

void print_action(t_data *data, int id, char *str)
{
	printf("%ldms %d %s\n", ft_timenow() - data->start, id, str);
}

void ft_usleep(int time)
{
  long begin;

  begin = ft_timenow();
  while (ft_timenow() - begin < time )
  	usleep(time / 10);
}

long int ft_timenow(void)
{
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return ((size_t)current_time.tv_sec * 1000 +(size_t)current_time.tv_usec / 1000);
}