#include "philo.h"

void release_forks(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  pthread_mutex_unlock(&data->forks[philo->right_fork]);
  pthread_mutex_unlock(&data->forks[philo->left_fork]);
}


void eating(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  pthread_mutex_lock(&data->forks[philo->left_fork]);
  pthread_mutex_lock(&data->print);
  print_action(data, philo->id, "has taken a fork 🥄");
	pthread_mutex_unlock(&data->print);
  pthread_mutex_lock(&data->forks[philo->right_fork]);

    // pthread_mutex_lock(&data->print);
  if(data->dead == true || data->full == true)
  {
	  release_forks(philo);
    return;
  }
  else
  {
    pthread_mutex_lock(&data->print);
    print_action(data, philo->id, "has taken a fork 🥄");
    print_action(data, philo->id, "is eating 🍚");
    philo->time_last_meal = ft_timenow();
	  pthread_mutex_unlock(&data->print);
  }
    
  pthread_mutex_lock(&data->print);
  philo->nb_of_meals += 1;
  if(philo->nb_of_meals == data->nb_of_meals)
    data->belly += philo->nb_of_meals;
  if(data->belly == data->is_full)
  {
    release_forks(philo);
    data->full = true;
    printf("All philosophers have eaten 🎊\n");
	  pthread_mutex_unlock(&data->print);
    return;
  }
	pthread_mutex_unlock(&data->print);
  ft_usleep(philo->time_to_eat, data);
  release_forks(philo);
 
}



void sleeping(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  
  pthread_mutex_lock(&data->print);
  if(data->dead == true || data->full == true || data->nbphilos == 1)
  {
	  pthread_mutex_unlock(&data->print);
    return;
  }
  print_action(data, philo->id, "is sleeping 💤");
	pthread_mutex_unlock(&data->print);
  ft_usleep(philo->time_to_sleep, data);
}

void thinking(t_philo *philo)
{
  t_data *data;

  data = philo->data;
  pthread_mutex_lock(&data->print);
  if(data->dead == true || data->full == true || data->nbphilos == 1)
  {
	  pthread_mutex_unlock(&data->print);
    return;
  }
  print_action(data, philo->id, "is thinking 🧠");
	pthread_mutex_unlock(&data->print);
}