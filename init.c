#include "philo.h"

void *init_threads(s_philo *philo, char **av)
{
  int i;
  int nbofphilos;

  philo->begin_time = ft_timenow();
  i = 0;
  philo->is_dead = 0;
  nbofphilos = ft_atoi(av[1]);
  philo->numphilos = nbofphilos;
  philo->time_to_die = atof(av[2]);
  philo->time_to_eat = atof(av[3]);
  philo->time_to_sleep = atof(av[4]);
  philo->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * nbofphilos);
  philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbofphilos);
  philo->current_phil = malloc(sizeof(s_currentphilo) * nbofphilos);
  if (av[5])
    philo->many_times_to_eat = atoi(av[5]);
  while (i < nbofphilos)
  {
    philo[i].forks = philo->forks;
    philo->thread_id[i] = i;
    philo[i].id = i;
    philo[i].numphilos = nbofphilos;
    i++;
  }
  return (NULL);
}