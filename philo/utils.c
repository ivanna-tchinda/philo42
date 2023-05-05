#include "philo.h"

int check_nb_meals(t_philo *philo)
{
  int i;
  t_data *data;

  data = philo->data;
  i = 0;
  while(i < philo->nbphilos)
  {
    if(philo[i].nb_of_meals > 0)
    {
      return 0;
    }
    i++;
  } 
  pthread_mutex_lock(&data->print);
  printf("All philos have eaten 🥳\n");
  pthread_mutex_unlock(&data->print);
  return(1);
}

void print_action(t_data *data, int id, char *str)
{
	printf("%lldms %d %s\n", ft_timenow() - data->start, id, str);
}

void ft_usleep(int time, t_philo *philo)
{
  long begin;

  begin = ft_timenow();
  while (ft_timenow() - begin < time && philo->is_dead == 0)
  	usleep(time / 10);
}

long int ft_timenow(void)
{
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return ((size_t)current_time.tv_sec * 1000 +(size_t)current_time.tv_usec / 1000);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	value;
	int	sign;

	i = 0;
	value = 0;
	sign = 1;
	while ((nptr[i] >= 7 && nptr[i] <= 13) || nptr[i] == ' ' || &nptr[i] == 0)
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-' && (nptr[i + 1] == '+' || nptr[i + 1] == '-'))
			return (0);
		else if (nptr[i] == '+' && (nptr[i + 1] == '-' || nptr[i + 1] == '+'))
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value = value * 10 + nptr[i] - '0';
		i++;
	}
	return (value * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}