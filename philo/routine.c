#include "philo.h"

void *routine_func(void *args)
{
  t_philo *philo;

  philo = (t_philo *)args;
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
  return(NULL);
}

void death_philo(t_philo *philo, int i)
{
  t_data *data;

  data = philo->data;
	pthread_mutex_lock(&data->print);
  philo[i].is_dead = 1;
  print_action(data, philo->id, "died 💀");
  i = 0;
  while(i < philo->nbphilos)
  {
    philo[i].is_dead = 1;
    i++; 
  }
}

void *supervisor(void *args)
{
  t_philo *philo;
  t_data *data;
  int i;

  philo = (t_philo *)args;
  data = philo->data;
  i = 0;
  while(philo[i].is_dead == 0)
  {
    i = 0;
    while(i < philo->nbphilos)
    {
      if(ft_timenow() - philo[i].time_last_meal > philo[i].time_to_die)
      {
        death_philo(philo, i);
        pthread_mutex_unlock(&data->print);
        return(NULL);
      }
      i++;
    }
    if(check_nb_meals(philo) == 1)
      return(NULL);
  }
  
  return(NULL);
}

void start_routine(t_data *data)
{
  pthread_t *thread_id;
  int i = 0;
  int status = 0;
  pthread_t thread2;
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
  pthread_create(&thread2, NULL, &supervisor, data->philo);
  pthread_join(thread2, NULL);
  data->tid = thread_id;
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