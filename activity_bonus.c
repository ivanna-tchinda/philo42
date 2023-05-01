#include "philo_bonus.h"

void release_forks(t_data *data)
{
  sem_post(data->forks);
  sem_post(data->forks);
}

void eating(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  if(data->is_dead == 1)
    return;
  sem_wait(data->forks);
  printf("ok\n");
  sem_wait(data->forks);
  sem_wait(data->print);
  if(philo->is_dead == 0)
  {
    print_action(data, philo->id, "has taken a fork 🍴");
    print_action(data, philo->id, "has taken a fork 🍴");
    print_action(data, philo->id, "is eating 🍚");
  }
  sem_close(data->print);
  philo->time_last_meal = ft_timenow();
  sem_wait(data->lock);
  philo->nb_of_meals -= 1;
  sem_close(data->lock);
  ft_usleep(philo->time_to_eat, philo);
  release_forks(data);
}

void sleeping(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  
  sem_wait(data->print);
  if(philo->is_dead == 0)
    print_action(data, philo->id, "is sleeping");
  sem_close(data->print);
  ft_usleep(philo->time_to_sleep, philo);
}

void thinking(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  if(philo->is_dead == 0)
  {
    sem_wait(data->print);
    print_action(data, philo->id, "is thinking");
    sem_close(data->print);
  }
}