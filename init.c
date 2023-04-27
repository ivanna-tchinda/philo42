#include "philo.h"

s_philo *init_threads(char **av, int ac)
{
  int i;
  int nbofphilos;
  s_philo *philo;

  i = 0;
  nbofphilos = ft_atoi(av[1]);
  philo = (s_philo *)malloc(sizeof(s_philo) * nbofphilos);
  philo->is_dead = 0;
  philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbofphilos);
  while (i < nbofphilos)
  {
    if (ac == 6 && av[5])
    {
      philo[i].many_times_to_eat = ft_atoi(av[5]);
    }
    else
      philo[i].many_times_to_eat = -1;
    philo[i].time_to_die = ft_atoi(av[2]);
    philo[i].time_to_eat = ft_atoi(av[3]);
    philo[i].time_to_sleep = ft_atoi(av[4]);
    philo[i].numphilos = nbofphilos;
    philo[i].thread_id = i;
    philo[i].begin_time = ft_timenow();
    philo[i].forks = philo->forks;
    philo[i].id = i;
    philo[i].numphilos = nbofphilos;
    i++;
  }
  return (philo);
}