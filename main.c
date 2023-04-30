#include "philo.h"



int main(int ac, char **av)
{
  t_data data;
  init_data(&data, ac, av);
  init_mutex(&data);
  init_philo(&data);
  start_routine(&data);
  end_routine(&data);
  return(0);
}