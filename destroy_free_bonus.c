#include "philo_bonus.h"

void destroy_free(t_data *data)
{
  sem_close(data->forks);
  sem_close(data->print);
  sem_close(data->lock);
}