#include "philo.h"

int check_nb_meals(t_philo *philo)
{
  int i;
  t_data *data;

  data = philo->data;
  i = 0;
  while(i < philo->nbphilos)
  {
    if(philo[i].nb_of_meals > 0)
    {
      return 0;
    }
    i++;
  } 
  pthread_mutex_lock(&data->print);
  printf("All philos have eaten 🥳\n");
  pthread_mutex_unlock(&data->print);
  return(1);
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