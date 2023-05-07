#include "philo.h"

void *routine_func(void *args)
{
  t_philo *philo;
  t_data *data;

  philo = (t_philo *)args;
  data = philo->data;
  philo->start_time = ft_timenow();
  philo->time_last_meal = ft_timenow();
  while(data->dead == false && data->full == false)
  {
    eating(philo);
    if(data->dead == false || data->full == false)
      sleeping(philo);
    if(data->dead == false || data->full == false)
      thinking(philo);
  }
  return(NULL);
}

void *death_philo(void *args)
{
  t_data *data;

  data = (t_data *)args;
  int i;

  i = 0;
  while(data->full == false)
  {
    i = 0;
    while(i < data->nbphilos)
    {
      if(ft_timenow() - data->philo[i].time_last_meal > data->time_to_die && data->full == false)
      {
        if(data->nbphilos == 1)
          pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
	      pthread_mutex_lock(&data->print);
        print_action(data, i, "died 💀");
        data->dead = true;
	      pthread_mutex_unlock(&data->print);
        return(NULL);
      }
      i++;
    }
  }
  return(NULL);
}

/*void *supervisor(void *args)
{
  t_philo *philo;
  t_data *data;
  int i;

  philo = (t_philo *)args;
  data = philo->data;
  (void)data;
  i = 0;
  while(data->dead == 0)
  {
    if(ft_timenow() - philo->time_last_meal > philo->time_to_die)
    {
      death_philo(philo, philo->id);
      return(NULL);
    }
    if(check_nb_meals(philo) == 1)
      return(NULL);
    i++;
  }
  
  return(NULL);
}*/

void start_routine(t_data *data)
{
  pthread_t *thread_id;
  int i = 0;
  int status = 0;
  (void)status;
  thread_id = malloc(sizeof(pthread_t) * data->nbphilos);
  data->start = ft_timenow();
  while (i < data->nbphilos)
  {
    if(pthread_create(&thread_id[i], NULL, &routine_func, &data->philo[i]) != 0)
    {
      status = write(1, "failed to create\n", 14);
      return;
    }
    i++;
  }
  pthread_create(&data->thread2, NULL, death_philo, data);
  pthread_detach(data->thread2);
  // pthread_join(data->thread2, NULL);
  data->tid = thread_id;
  return;
}

void end_routine(t_data *data)
{
  int i;

  i = 0;
  while(i < data->nbphilos)
  {
    pthread_join(data->tid[i], NULL);
    i++;
  }
}