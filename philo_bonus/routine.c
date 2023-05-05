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
  sem_close(data->death);
  sem_close(data->full);
  sem_close(data->print);
  sem_close(data->forks);
  free(data->philo_id);
  printf("All philos have eaten!\n");
  exit(0);
}

void *death(void *args)
{
    t_data *data;

    data = (t_data *)args;
    (void)data;
    sem_wait(data->death);
    sem_close(data->death);
    sem_close(data->full);
    sem_close(data->print);
    sem_close(data->forks);
    free(data->philo_id);
    //kill_process(data);
    exit(0);
    return(NULL);
}

void start_routine(t_data *data)
{
  int i;

  i = 0;
  data->start = ft_timenow();
  if(pthread_create(&data->death_thread, NULL, &death, data) != 0)
    return;
  if(pthread_create(&data->supervisor, NULL, &supervisor, data) != 0)
    return;
  while(i < data->nbphilos)
  {
    data->philo.id = i;
    data->philo_id[i] = fork();
    if(data->philo_id[i] == -1)
    {
      printf("process failed\n");
      return;
    }
    if(data->philo.id % 2 != 0)
      usleep(2);
    if(data->philo_id[i] == 0)
    {
      init_philo(data);
      routine_func(data);
    }
    i++;
  }
  pthread_join(data->death_thread, NULL);
  pthread_join(data->supervisor, NULL);
}

void routine_func(t_data *data)
{
  //data->start = ft_timenow();
  while(1)
  {
    if(ft_timenow() - data->philo.time_last_meal > data->time_to_die || data->nbphilos == 1)
    {
        sem_wait(data->print);
        print_action(data, data->philo.id, "died 💀");
        sem_post(data->death);
    }
    eating(data);
    sleep_think(data);
  }
}
