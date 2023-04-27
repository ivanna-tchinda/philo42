
#include "philo.h"

void *check_death(s_philo *philo, int i)
{
  print_activity(philo[i].id, "died 💀", philo);
  i = 0;
  while(i < philo->numphilos)
  {
    philo[i].is_dead = 1;
    i++;
  }
  return(NULL);
}

void *supervisor(void *arg)
{
  s_philo *philo = (s_philo *)arg;
  long int time;
  time = ft_timenow();
  int i;
  i = 0;
  while(i < philo->numphilos)
  {
    if (time - philo[i].eat_time >= philo[i].time_to_die)
    {
      check_death(philo, i);
      printf("superv: id %d is %ddead\n", philo[i].id, philo[i].is_dead);
      return(NULL);
    }
    i++;
  }
  return(NULL);
}


void *routine_func(void *arg)
{
  s_philo philo = *(s_philo *)arg;

  if(philo.id % 2 != 0)
    ft_usleep(philo.time_to_eat);
  while ((&philo)->is_dead == 0 && philo.many_times_to_eat != 0)
  {
    printf("routine: id %d is %ddead\n", philo.id, philo.is_dead);
    if(philo.is_dead == 0)
      eating_routine(&philo);
    if(philo.is_dead == 0)
    sleeping_routine(&philo);
    if(philo.is_dead == 0)
    thinking_routine(&philo);
    check_all_ate(&philo, philo.many_times_to_eat);
  }
  return (NULL);
}


void *start_routine(s_philo *philo)
{
  int i = 0;
  int status = 0;
  (void)status;
  while (i < philo->numphilos)
  {
    if(pthread_create(&philo[i].thread_id, NULL, &routine_func, &philo[i]) != 0)
    {
      //end_routine(philo);
      status = write(1, "failed to create\n", 14);
      return (NULL);
    }
    i++;
  }
  pthread_create(&philo->monitor, NULL, &supervisor, philo);
  if(pthread_join(philo->monitor, NULL) != 0)
    printf("failed to join\n");
  return (NULL);
}

void *end_routine(s_philo *philo)
{
  int i;
  int status = 0;
  (void)status;
  // join threads
  i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_join(philo[i].thread_id, NULL) != 0)
    {
      status = write(1, "failed to join\n", 15);
      return(NULL);
    }
    i++;
  }
  return (NULL);
}

void check_all_ate(s_philo *philo, int eat)
{
  int i;

  i = 0;
  if(eat == -1)
    return;
  while(i < philo->numphilos)
  {
    if(philo->many_times_to_eat != 0)
    {
      return;
    }
    i++;
  }
  printf("All philosophers ate.\n");
  //end_routine(philo);
}

int main(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    return (write(1, "Invalid number of arguments\n", 28));
  s_philo *philo;
  philo = init_threads(av, ac);
  start_routine(philo);
  end_routine(philo);
  destroy_mutex(philo);
  //free_philo(philo);
  return (0);
}