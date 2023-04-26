#include "philo.h"

void *eating_routine(s_philo *philo)
{
  init_mutex(philo);
  if (philo->id % 2 == 0 && (philo->id + 1) != philo->numphilos)
  {
    taking_forks(philo);
  }
  else
  {
    taking_forks2(philo);
  }
  return (NULL);
}


void *sleeping_routine(s_philo *philo)
{
  
  print_activity(philo->id, "is sleeping", philo);

  ft_usleep(philo->time_to_sleep);
  return (NULL);
}

void *thinking_routine(s_philo *philo)
{
  print_activity(philo->id, "is thinking", philo);
  
  return (NULL);
}