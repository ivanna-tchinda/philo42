#include "philo_bonus.h"

void *check_nb_meals(void *arg)
{
  t_data *data;

  data = (t_data *)arg;
  int i;
  i = 0;
  sem_post(data->print);
  while(i < data->nbphilos)
  {
    sem_wait(data->print);
    //sem_wait(data->eat);
    sem_post(data->print);
    i++;
  }
  printf("All philos have eaten 🥳\n");
  exit(0);
  return(NULL);
}

void print_action(t_data *data, int id, char *str)
{
	printf("%lldms %d %s\n", ft_timenow() - data->start, id, str);
}

void ft_usleep(int time, t_philo *philo)
{
  long begin;

  begin = ft_timenow();
  while (ft_timenow() - begin < time && philo->is_dead == 0)
  	usleep(time / 10);
}

long int ft_timenow(void)
{
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return ((size_t)current_time.tv_sec * 1000 +(size_t)current_time.tv_usec / 1000);
}