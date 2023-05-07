#include "philo_bonus.h"

void init_semaphores(t_data *data)
{
  sem_unlink("forks");
  sem_unlink("print");
  sem_unlink("full");
  sem_unlink("death");

  data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, data->nbphilos);
  data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
  data->full = sem_open("full", O_CREAT | O_EXCL, S_IRWXU, 0);
  data->death = sem_open("death", O_CREAT | O_EXCL, S_IRWXU, 0);
}

void init_philo(t_data *data)
{
  pthread_t thread_philo;
  data->philo.time_to_die = data->time_to_die;
  data->philo.time_to_eat = data->time_to_eat;
  data->philo.time_to_sleep = data->time_to_sleep;
  data->philo.nb_of_meals = 0;
  data->philo.nbphilos = data->nbphilos;
  data->philo.data = data;
  data->philo.time_last_meal = ft_timenow();
  data->philo_thread = thread_philo;
  pthread_create(&thread_philo, NULL, &death, data);
  pthread_detach(thread_philo);
}

void init_data(t_data *data, int ac, char **av)
{
  memset(data, 0, sizeof(t_data));
  data->dead = false;
  data->nbphilos = atoi(av[1]);
  data->time_to_die = atoi(av[2]);
  data->time_to_eat = atoi(av[3]);
  data->time_to_sleep = atoi(av[4]);
  if(ac == 6)
    data->nb_of_meals = atoi(av[5]);
  else
    data->nb_of_meals = -1;
}