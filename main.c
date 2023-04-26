
#include "philo.h"



void *routine_func(void *arg)
{
  s_philo *philo = (s_philo *)arg;
  while (1)
  {
    eating_routine(philo);
    sleeping_routine(philo);
    thinking_routine(philo);
  }
  return (NULL);
}


void *start_routine(s_philo *philo)
{
  int i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_create(&philo[i].thread_id, NULL, &routine_func, &philo[i]) != 0)
    {
      exit(write(1, "failed thread\n", 14));
      return (NULL);
    }
    i++;
    // create threads for each philo with routine func
  }
  return (NULL);
}

void *end_routine(s_philo *philo)
{
  int i;
  // join threads
  i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_join(philo[i].thread_id, NULL) != 0)
    {
      exit(write(1, "failed to join\n", 15));
      return(NULL);
    }
    i++;
  }
  return (NULL);
}

int main(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    return (write(1, "Invalid number of arguments\n", 28));
  s_philo philo;
  init_threads(&philo, av);
  start_routine(&philo);
  printf("Number of threads created: %ld\n", pthread_self());
  end_routine(&philo);
  destroy_mutex(&philo);
  return (0);
}