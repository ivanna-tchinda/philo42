#include "philo_bonus.h"


void eating(t_data *data)
{
  sem_wait(data->forks);
  sem_wait(data->forks);


  sem_wait(data->print);
  print_action(data, data->philo.id, "has taken a fork 🥄");
  sem_post(data->print);
  sem_wait(data->print);
  print_action(data, data->philo.id, "has taken a fork 🥄");
  sem_post(data->print);
  sem_wait(data->print);
  print_action(data, data->philo.id, "is eating 🍚");
  sem_post(data->print);
    
  data->philo.time_last_meal = ft_timenow();
  data->philo.nb_of_meals += 1;
  if(data->philo.nb_of_meals == data->nb_of_meals)
    sem_post(data->full);
  ft_usleep(data->time_to_eat, data->philo.time_last_meal, data);
    
  sem_post(data->forks);
  sem_post(data->forks);
}

void sleep_think(t_data *data)
{
  sem_wait(data->print);
  print_action(data, data->philo.id, "is sleeping 💤");
  sem_post(data->print);
  ft_usleep(data->time_to_sleep, data->philo.time_last_meal, data);
  sem_wait(data->print);
  print_action(data, data->philo.id, "is thinking 🧠");
  sem_post(data->print);
}