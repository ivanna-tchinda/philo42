
#include "philo.h"



void *routine_func(void *arg)
{
  s_philo philo = *(s_philo *)arg;
  while (1)
  {
    eating_routine(&philo);
    sleeping_routine(&philo);
    thinking_routine(&philo);
  }
  return (NULL);
}


void *start_routine(s_philo *philo)
{
  int i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_create(&philo->thread_id[i], NULL, &routine_func, &philo[i]) != 0)
    {
      write(1, "thread failed\n", 14);
      break;
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
    pthread_join(philo->thread_id[i], NULL);
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
  end_routine(&philo);
  destroy_mutex(&philo);
  return (0);
}