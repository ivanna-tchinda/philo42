#include "philo_bonus.h"

int ft_parse(int ac, char **av)
{
  int i;
  int j;

  i = 1;
  if (ac < 5 || ac > 6)
  {
    printf("Enter 5 or 6 digits\n");
    return(1);
  }
  while(i < ac)
  {
    j = 0;
    while(j < (int)ft_strlen(av[i]))
    {
      if(!(av[i][j] <= 57 && av[i][j] >= 48))
      {
        printf("Enter 5 or 6 digits\n");
        return(1);
      }
      j++;
    }
    if(ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
    {
      printf("Enter only integers superior to 0\n");
      return(1);
    }
    i++;
  }
  if(ft_strncmp(av[ac - 1], "0", 1) == 0)
  {
    printf("Philosophers don't need to eat\n");
    return(1);
  }
  return(0);
}

int main(int ac, char **av)
{
  if(ft_parse(ac, av) == 1)
    return(1);
  t_data data;
  init_data(&data, ac, av);
  // init_philo(&data);
  init_semaphores(&data);
  start_routine(&data);
  // end_threads(&data);
  kill_process(&data);

  return(0);
}