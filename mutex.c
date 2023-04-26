#include "philo.h"

void *init_mutex(s_philo *philo)
{
  int i;

  philo->forks = malloc(sizeof(pthread_mutex_t) * philo->numphilos);
  if (!philo->forks)
    exit(1);
  i = 0;
  while (i < philo->numphilos)
  {
    if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
      exit(1);
    i++;
  }
  pthread_mutex_init(&philo->lock, NULL);
  return(NULL);
}

void *destroy_mutex(s_philo *philo)
{
  pthread_mutex_destroy(&philo[philo->id].forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_destroy(&philo->forks[philo->id]);
  pthread_mutex_destroy(&philo->lock);
  return(NULL);
}
