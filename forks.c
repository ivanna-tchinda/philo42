#include "philo.h"

void print_activity(int id, char *activity, s_philo *philo)
{
  long int time = ft_timenow() - philo->begin_time;
  if(time >= 0 && time <= INT_MAX)
  {
    while(pthread_mutex_lock(&philo->lock) != 0)
      ft_usleep(1);
    printf("%ldms %d %s\n", time, id, activity);
    pthread_mutex_unlock(&philo->lock);
  }
}

void *release_forks2(s_philo *philo)
{
  pthread_mutex_unlock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]);
  pthread_mutex_unlock(&philo->forks[philo->id]);
  return(NULL);
}

void *taking_forks2(s_philo *philo)
{
  while(pthread_mutex_lock(&philo->forks[philo->id]) != 0)
    ft_usleep(1);
  
  print_activity(philo->id, "has taken a fork", philo);
  
  while(pthread_mutex_lock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]) != 0)
    ft_usleep(1);
    
  
  print_activity(philo->id, "has taken a fork", philo);

  print_activity(philo->id, "is eating", philo);

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
  while(pthread_mutex_lock(&philo->forks[philo->id]) != 0)
    ft_usleep(1);
  
  print_activity(philo->id, "has taken a fork", philo);
  
  while(pthread_mutex_lock(&philo->forks[(philo->id + philo->numphilos - 1) % (philo->numphilos)]) != 0)
    ft_usleep(1);
  
  
  print_activity(philo->id, "has taken a fork", philo);

  print_activity(philo->id, "is eating", philo);
  
  ft_usleep(philo->time_to_eat);

  release_forks(philo);
  return (NULL);
}