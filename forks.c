#include "philo.h"

void *release_forks2(s_philo *philo)
{
  pthread_mutex_unlock(&philo->forks[philo->id]);
  pthread_mutex_unlock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  return(NULL);
}

void *taking_forks2(s_philo *philo)
{
  pthread_mutex_lock(&philo->forks[philo->id]);
  pthread_mutex_lock(&philo->lock);
  if(ft_timenow() - philo->begin_time >= 0 && (ft_timenow() - philo->begin_time) <= INT_MAX)
    printf("%ldms %d has taken a fork\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);
  pthread_mutex_lock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_lock(&philo->lock);
  if(ft_timenow() - philo->begin_time >= 0 && (ft_timenow() - philo->begin_time) <= INT_MAX)
    printf("%ldms %d has taken a fork\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);

  pthread_mutex_lock(&philo->lock);
  if(ft_timenow() - philo->begin_time >= 0 && (ft_timenow() - philo->begin_time) <= INT_MAX)
    printf("%ldms %d is eating\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);
  ft_usleep(philo->time_to_eat);
  release_forks2(philo);
  return (NULL);
}

void *release_forks(s_philo *philo)
{
  pthread_mutex_unlock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_unlock(&philo->forks[philo->id]);
  return(NULL);
}

void *taking_forks(s_philo *philo)
{
  long int time = ft_timenow() - philo->begin_time;
  pthread_mutex_lock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_lock(&philo->lock);
  if(time >= 0 && time <= INT_MAX)
    printf("%ldms %d has taken a fork\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);
  pthread_mutex_lock(&philo->forks[philo->id]);
  pthread_mutex_lock(&philo->lock);
  if(time >= 0 && time <= INT_MAX)
    printf("%ldms %d has taken a fork\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);

  pthread_mutex_lock(&philo->lock);
  if(time >= 0 && time <= INT_MAX)
    printf("%ldms %d is eating\n", ft_timenow() - philo->begin_time, philo->id);
  pthread_mutex_unlock(&philo->lock);
  gettimeofday(&philo->current_time, NULL);
  ft_usleep(philo->time_to_eat);

  release_forks(philo);
  return (NULL);
}