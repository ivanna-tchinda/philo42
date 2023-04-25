#include "philo.h"

void *destroy_mutex(s_philo *philo)
{
  pthread_mutex_destroy(&philo[philo->id].forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_destroy(&philo->forks[philo->id]);
  pthread_mutex_destroy(&philo->lock);
  return(NULL);
}

void *init_mutex(s_philo *philo)
{
  pthread_mutex_init(&philo->forks[philo->id], NULL);
  pthread_mutex_init(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)], NULL);
  pthread_mutex_init(&philo->lock, NULL);
  return(NULL);
}