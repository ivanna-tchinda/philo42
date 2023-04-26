#include "philo.h"


void ft_usleep(float time)
{
  long int begin;
  (void)begin;

  begin = ft_timenow();
  //while (ft_timenow() - begin < time)
  usleep(time);
}

long int ft_timenow(void)
{
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;
	size_t	total;

	i = 0;
	total = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size && nmemb / SIZE_MAX > size)
		return (NULL);
	str = (void *)malloc(total);
	if (!str)
		return (NULL);
	while (i < total)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}