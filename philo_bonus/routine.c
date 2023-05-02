#include "philo_bonus.h"

void ft_routine(t_philo *philo)
{
  pthread_t thread2;

  philo->start_time = ft_timenow();
  pthread_create(&thread2, NULL, &supervisor, philo);
  while(philo->is_dead == 0)
  {
    if(philo->is_dead == 1)
      break;
    eating(philo);
    philo->time_last_meal = ft_timenow();
    if(philo->is_dead == 1)
      break;
    sleeping(philo);
    if(philo->is_dead == 1)
      break;
    thinking(philo);
    if(philo->is_dead == 1)
      break;
  }
  pthread_join(thread2, NULL);
}

void death_philo(t_philo *philo, int i)
{
  t_data *data;

  data = philo->data;
	sem_wait(data->print);
  philo[i].is_dead = 1;
  print_action(data, philo->id, "died 💀");
  exit(0);
}

void *supervisor(void *args)
{
  t_philo *philo;
  t_data *data;
  int i;

  philo = (t_philo *)args;
  data = philo->data;
  i = 0;
  philo->time_last_meal = ft_timenow();
  while(1)
  {
    if(ft_timenow() - philo->time_last_meal > philo->time_to_die)
    {
      death_philo(philo, i);
      sem_post(data->print);
      return(NULL);
    }
  }
  
  return(NULL);
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
  data->start = ft_timenow();
  while(i < philo->nbphilos)
  {
    pid[i] = fork();
    if(pid[i] == -1)
      return(NULL);
    if(pid[i] == 0)
      ft_routine(&philo[i]);
    i++;
  }
  pid = data->pid;
  return(NULL);
}

void kill_process(t_data *data)
{
  int i;

  i = 0;
  while(i < data->nbphilos)
  {
    kill(data->pid[i], SIGKILL);
    i++;
  }
}

void start_check_eating(t_data *data)
{
  pthread_t thread_id2;
  pthread_create(&thread_id2, NULL, &check_nb_meals, (void *)data);
  pthread_detach(thread_id2);
}

void start_routine(t_data *data)
{
  pthread_t thread_id;
  
  pthread_create(&thread_id, NULL, &ft_process, (void *)data);
  pthread_join(thread_id, NULL);
}