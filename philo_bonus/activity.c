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
  sem_wait(data->forks);
  sem_wait(data->print);
  if(philo->is_dead == 0)
  {
    print_action(data, philo->id, "has taken a fork 🍴");
    print_action(data, philo->id, "has taken a fork 🍴");
    print_action(data, philo->id, "is eating 🍚");
  }
  sem_post(data->print);
  sem_wait(data->print);
  philo->time_last_meal = ft_timenow();
  sem_post(data->print);
  philo->nb_of_meals += 1;
  ft_usleep(philo->time_to_eat, philo);
  release_forks(data);
  if(philo->nb_of_meals == data->nb_of_meals)
    sem_post(data->eat);
}

void sleeping(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  
  sem_wait(data->print);
  if(philo->is_dead == 0)
    print_action(data, philo->id, "is sleeping");
  sem_post(data->print);
  ft_usleep(philo->time_to_sleep, philo);
}

void thinking(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  sem_wait(data->print);
  if(philo->is_dead == 0)
    print_action(data, philo->id, "is thinking");
  sem_post(data->print);
}