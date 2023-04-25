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
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);
  gettimeofday(&philo->current_time, NULL);
  pthread_mutex_lock(&lock);
  if(ft_timenow() - philo->begin_time >= 0 && (ft_timenow() - philo->begin_time) <= INT_MAX)
    printf("%ldms %d is sleeping\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&lock);
  pthread_mutex_unlock(&lock);
  ft_usleep(philo->time_to_sleep);
  return (NULL);
}

void *thinking_routine(s_philo *philo)
{
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);
  pthread_mutex_lock(&lock);
  if(ft_timenow() - philo->begin_time >= 0 && (ft_timenow() - philo->begin_time) <= INT_MAX)
    printf("%ldms %d is thinking\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&lock);
  pthread_mutex_unlock(&lock);
  return (NULL);
}

