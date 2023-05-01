#include "philo_bonus.h"

void init_sem(t_data *data)
{
  sem_unlink("fork");
  sem_unlink("print");
  sem_unlink("lock");
  data->forks = sem_open("fork", data->nbphilos);
  data->forks = sem_open("print", 1);
  data->forks = sem_open("lock", 1);
}

void init_philo(t_data *data)
{
  t_philo *philo;
  int i;

  philo = malloc(sizeof(t_philo) * data->nbphilos);
  i = 0;
  while (i < data->nbphilos)
  {
    philo[i].id = i;
    philo[i].time_to_die = data->time_to_die;
    philo[i].time_to_eat = data->time_to_eat;
    philo[i].time_to_sleep = data->time_to_sleep;
    philo[i].nb_of_meals = data->nb_of_meals;
    philo[i].left_fork = i;
    philo[i].right_fork = (i + 1) % data->nbphilos;
    philo[i].nbphilos = data->nbphilos;
    philo[i].data = data;
    philo[i].time_last_meal = ft_timenow();
    philo[i].is_dead = 0;
    i++;
  }
  data->philo = philo;
}

void init_data(t_data *data, int ac, char **av)
{
  data->nbphilos = atoi(av[1]);
  data->time_to_die = atoi(av[2]);
  data->time_to_eat = atoi(av[3]);
  data->time_to_sleep = atoi(av[4]);
  data->is_dead = 0;
  if(ac == 6)
    data->nb_of_meals = atoi(av[5]);
  else
    data->nb_of_meals = ULONG_MAX;
}