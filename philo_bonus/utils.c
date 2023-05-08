/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:06:42 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 13:08:34 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_data *data, int id, char *str)
{
	printf("%ldms %d %s\n", ft_timenow() - data->start, id, str);
}

void	ft_usleep(int time)
{
	long	begin;

	begin = ft_timenow();
	while (ft_timenow() - begin < time)
		usleep(time / 10);
}

long int	ft_timenow(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((size_t)current_time.tv_sec * 1000
		+ (size_t)current_time.tv_usec / 1000);
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
