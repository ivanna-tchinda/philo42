#include "philo_bonus.h"

void ft_routine(t_philo *philo)
{
  philo->start_time = ft_timenow();
  while(philo->is_dead == 0 && philo->nb_of_meals > 0)
  {
    philo->time_last_meal = ft_timenow();
    if(philo->is_dead == 1 || philo->nb_of_meals == 0)
      break;
    eating(philo);
    if(philo->is_dead == 1 || philo->nb_of_meals == 0)
      break;
    sleeping(philo);
    if(philo->is_dead == 1 || philo->nb_of_meals == 0)
      break;
    thinking(philo);
    if(philo->is_dead == 1 || philo->nb_of_meals == 0)
      break;
  }
}

void *ft_process(void *args)
{
  t_data  *data;
  t_philo *philo;
  int *pid;
  int i;

  data = (t_data *)args;
  philo = data->philo;
  pid = malloc(sizeof(int) * philo->nbphilos);
  i = 0;
  while(i < philo->nbphilos)
  {
    pid[i] = fork();
    if(pid[i] == -1)
      return(NULL);//exit&free
    if(pid[i] == 0)
      ft_routine(&philo[i]);
    i++;
  }
  return(NULL);
}

void start_routine(t_data *data)
{
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, &ft_process, (void *)data);
  pthread_join(thread_id, NULL);
}