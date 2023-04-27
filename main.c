
#include "philo.h"

int check_death(s_philo philo)
{
  long int time;

  time = ft_timenow();
  if (time - philo.eat_time >= philo.time_to_die)
  {
    (&philo)->is_dead = 1;
    print_activity(philo.id, "died 💀", &philo);
    return 1;
  }
  return 0;
}

void *routine_func(void *arg)
{
  s_philo philo = *(s_philo *)arg;

  if(philo.id % 2 != 0)
    ft_usleep(philo.time_to_eat);
  while ((&philo)->is_dead == 0 && philo.many_times_to_eat != 0)
  {
    eating_routine(&philo);
    sleeping_routine(&philo);
    thinking_routine(&philo);
    if(check_death(philo) != 0)
    {
      exit(0);
      break;
    }
    pthread_detach(philo.thread_id);
    check_all_ate(&philo, philo.many_times_to_eat);
  }
  return (NULL);
}


void *start_routine(s_philo *philo)
{
  int i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_create(&philo[i].thread_id, NULL, &routine_func, &philo[i]) != 0)
    {
      exit(write(1, "failed to create\n", 14));
      return (NULL);
    }
    i++;
    // create threads for each philo with routine func
  }
  return (NULL);
}

void *end_routine(s_philo *philo)
{
  int i;
  // join threads
  i = 0;
  while (i < philo->numphilos)
  {
    if(pthread_join(philo[i].thread_id, NULL) != 0)
    {
      exit(write(1, "failed to join\n", 15));
      return(NULL);
    }
    i++;
  }
  return (NULL);
}

void check_all_ate(s_philo *philo, int eat)
{
  int i;

  i = 0;
  if(eat == -1)
    return;
  while(i < philo->numphilos)
  {
    if(philo->many_times_to_eat != 0)
    {
      return;
    }
    i++;
  }
  printf("All philosophers ate.\n");
  exit(0);
}

int main(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    return (write(1, "Invalid number of arguments\n", 28));
  s_philo philo;
  init_threads(&philo, av);
  start_routine(&philo);
  end_routine(&philo);
  destroy_mutex(&philo);
  free_philo(&philo);
  return (0);
}