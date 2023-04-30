#include "philo.h"

int check_nb_meals(t_philo *philo)
{
  int i;

  i = 0;
  while(i < philo->nbphilos)
  {
    if(philo->nb_of_meals > 0)
    {
      return 0;
    }
    i++;
  } 
  printf("All philos have eaten\n");
  return(1);
}

void print_action(t_data *data, int id, char *str)
{
  pthread_mutex_lock(&data->print);
  printf("%lldms %d %s\n", ft_timenow() - data->start, id, str);
  pthread_mutex_unlock(&data->print);
}

void ft_usleep(int time)
{
  long begin;

  begin = ft_timenow();
  while (ft_timenow() - begin < time)
  	usleep(time / 10);
}

long int ft_timenow(void)
{
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return ((size_t)current_time.tv_sec * 1000 +(size_t)current_time.tv_usec / 1000);
}