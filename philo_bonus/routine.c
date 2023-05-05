#include "philo_bonus.h"

void *supervisor(void *args)
{
  t_data *data;
  int i;

  data = (t_data *)args;
  i = 0;
  while(i < data->nbphilos)
  {
    sem_wait(data->full);
    i++;
  }
  sem_wait(data->print);
  printf("All philos have eaten!\n");
  sem_post(data->death);
  return NULL;
}

void *death(void *args)
{
    t_data *data;

    data = (t_data *)args;
    (void)data;
    while (1)
    {
      if(ft_timenow() - data->philo.time_last_meal > data->time_to_die || data->nbphilos == 1)
      {
        sem_wait(data->print);
        print_action(data, data->philo.id, "died 💀");
        sem_post(data->death);
        break;
      }
    }
    return(NULL);
}

void start_routine(t_data *data)
{
  int i;

  i = 0;
  data->start = ft_timenow();
  pthread_create(&data->supervisor, NULL, &supervisor, data);
  data->philo_id = malloc(sizeof(pid_t) * data->nbphilos);
  memset(data->philo_id, 0, sizeof(pid_t) * data->nbphilos);
  while(i < data->nbphilos)
  {
    data->philo.id = i;
    data->philo_id[i] = fork();
    if(data->philo_id[i] == -1)
    {
      printf("process failed\n");
      return;
    }
    if(data->philo_id[i] == 0)
    {
      if(data->philo.id % 2 == 0)
        usleep(3);
      init_philo(data);
      routine_func(data);
    }
    i++;
  }
  sem_wait(data->death);
  return;
}

void routine_func(t_data *data)
{
  data->philo.time_last_meal = ft_timenow();
  pthread_create(&data->death_thread, NULL, &death, data);
  while(1)
  {
    eating(data);
    sleep_think(data);
  }
  pthread_join(data->death_thread, NULL);
}