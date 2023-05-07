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
    sem_post(data->death);
    i++;
  }
  sem_wait(data->print);
  printf("All philos have eaten!\n");
  return NULL;
}

void *death(void *args)
{
    t_data *data;

    data = (t_data *)args;
    data->philo.time_last_meal = ft_timenow();
    while(1)
    {
      if(ft_timenow() - data->philo.time_last_meal > data->time_to_die)
      {
        printf("id %d dead\n", data->philo.id);
        sem_post(data->death);
        sem_wait(data->print);
        data->dead = true;
        print_action(data, data->philo.id, "died --------");
        // sem_post(data->print);
        // data->dead_philo = data->philo.id;
        break;
      }
    }
    printf("%d\n", data->dead);
    return(NULL);
}

void start_routine(t_data *data)
{
  int i;
  // pid_t *pid_philo;

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
      routine_func(data);
    }
    i++;
  }
  pthread_create(&data->philo_thread, NULL, &supervisor, data);
  pthread_detach(data->philo_thread);
  // data->philo_id = pid_philo;
  sem_wait(data->death);
  // sem_wait(data->death);
  printf("exit main routine %d\n", data->philo.id);
  sem_post(data->death);
  return;
}

void *routine_func(void *args)
{
  t_data *data;

  data = (t_data *)args;
  //data->start = ft_timenow();
  data->philo.time_last_meal = ft_timenow();
  while(1)
  {
    eating(data);
    sleep_think(data);
  }
  printf("exit routine loop%d\n", data->philo.id);
  sem_post(data->death);
  return(NULL);
}