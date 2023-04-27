#include "philo.h"

void *init_threads(s_philo *philo, char **av)
{
  int i;
  int nbofphilos;

  i = 0;
  nbofphilos = ft_atoi(av[1]);
  philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbofphilos);
  while (i < nbofphilos)
  {
    if (av[5])
      philo[i].many_times_to_eat = atoi(av[5]);
    else
      philo[i].many_times_to_eat = -1;
    philo[i].is_dead = 0;
    philo[i].time_to_die = atof(av[2]);
    philo[i].time_to_eat = atof(av[3]);
    philo[i].time_to_sleep = atof(av[4]);
    philo[i].numphilos = nbofphilos;
    philo[i].thread_id = i;
    philo[i].begin_time = ft_timenow();
    philo[i].forks = philo->forks;
    philo[i].id = i;
    philo[i].numphilos = nbofphilos;
    i++;
  }
  return (NULL);
}