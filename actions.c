#include "philo.h"

void release_forks(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  pthread_mutex_unlock(&data->forks[philo->right_fork]);
  pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void release_forks_else(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  pthread_mutex_unlock(&data->forks[philo->left_fork]);
  pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void eating(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  if(data->is_dead == 1)
    return;
  if(philo->id % 2 == 0 && philo->id + 1 != philo->nbphilos)
  {
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    printf("%d\n", philo->is_dead);
    print_action(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_action(data, philo->id, "has taken a fork");
    print_action(data, philo->id, "is eating");
    philo->time_last_meal = ft_timenow();
    pthread_mutex_lock(&data->lock);
    philo->nb_of_meals -= 1;
    pthread_mutex_unlock(&data->lock);
    ft_usleep(philo->time_to_eat);
    release_forks(philo);
    
  }
  else
    eating_else(philo);
}

void eating_else(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  if(data->is_dead == 1)
    return;
  pthread_mutex_lock(&data->forks[philo->right_fork]);
  print_action(data, philo->id, "has taken a fork");
  pthread_mutex_lock(&data->forks[philo->left_fork]);
  print_action(data, philo->id, "has taken a fork");
  print_action(data, philo->id, "is eating");
  philo->time_last_meal = ft_timenow();
  pthread_mutex_lock(&data->lock);
  philo->nb_of_meals -= 1;
  pthread_mutex_unlock(&data->lock);
  ft_usleep(philo->time_to_eat);
  release_forks_else(philo);
}



void sleeping(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  print_action(data, philo->id, "is sleeping");
  ft_usleep(philo->time_to_sleep);
}

void thinking(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  print_action(data, philo->id, "is thinking");
}