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
  sem_post(data->death);
  sem_wait(data->print);
  data->dead = true;
  printf("All philos have eaten!\n");
  // sem_post(data->print);
  return NULL;
}

void *death(void *args)
{
    t_data *data;

    data = (t_data *)args;
    (void)data;
    while(1)
    {
      if(ft_timenow() - data->philo.time_last_meal > data->time_to_die)
      {
        sem_wait(data->print);
        sem_post(data->death);
        print_action(data, data->philo.id, "died --------------");
        // printf("stuck here?\n");
        data->dead = true;
        // printf("or here? \n");
        // sem_post(data->death);
        // printf("no here \n");
        // exit(0);
        printf("exit\n");
        // sem_post(data->print);
        return(NULL);
      }
    }
    return(NULL);
}

void start_routine(t_data *data)
{
  int i;

  i = 0;
  data->start = ft_timenow();
  data->philo_id = malloc(sizeof(pid_t) * data->nbphilos);
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
      init_philo(data);
      data->philo.time_last_meal = ft_timenow();
      routine_func(data);
    }
    i++;
  }
  pthread_create(&data->death_thread, NULL, &supervisor, data);
  pthread_detach(data->death_thread);
  // printf("death\n");
  sem_wait(data->death);
  printf("main pid %d\n", getpid());
  return;
}

void *routine_func(void *args)
{
  t_data *data;

  data = (t_data *)args;
  data->philo.time_last_meal = ft_timenow();
  while(data->dead == false)
  {
    eating(data);
    if(data->dead == true)
      break;
    sleep_think(data);
    if(data->dead == true)
      break;
  }
  // sem_post(data->death);
  // printf("id %d exit %d\n", data->philo.id, getpid());
  return(NULL);
}
