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
    data->philo.time_last_meal = ft_timenow();
    while(1)
    {
      if(ft_timenow() - data->philo.time_last_meal > data->time_to_die)
      {
        printf("exit death monitor %d\n", data->philo.id);
        sem_post(data->death);
        sem_wait(data->print);
        data->dead = true;
        print_action(data, data->philo.id, "died --------");
        break;
      }
    }
    // exit(0);
    return(NULL);
}

void start_routine(t_data *data)
{
  int i;
  pid_t *pid_philo;

  i = 0;
  data->start = ft_timenow();
  pid_philo = malloc(sizeof(pid_t) * data->nbphilos);
  while(i < data->nbphilos)
  {
    data->philo.id = i;
    pid_philo[i] = fork();
    if(pid_philo[i] == -1)
    {
      printf("process failed\n");
      return;
    }
    if(pid_philo[i] == 0)
    {
      init_philo(data);
      routine_func(data);
    }
    i++;
  }
  data->philo_id = pid_philo;
  // sem_wait(data->death);
  printf("exit main routine %d\n", data->philo.id);
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
    if(data->dead == true)
      break;
    sleep_think(data);
    if(data->dead == true)
      break;
  }
  printf("exit routine loop%d\n", data->philo.id);
  return(NULL);
}