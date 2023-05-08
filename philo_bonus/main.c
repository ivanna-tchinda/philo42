/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:53:20 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:54:40 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (j < (int)ft_strlen(av[i]))
		{
			if (ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
			{
				printf("Enter 4 or 5 integers superior to 0\n");
				return (1);
			}
			if (!(av[i][j] <= 57 && av[i][j] >= 48))
			{
				printf("Enter 4 or 5 integers superior to 0\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_parse(ac, av) == 1)
		return (1);
	if (ac < 5 || ac > 6)
	{
		printf("Enter 4 or 5 integers superior to 0\n");
		return (1);
	}
	if (ft_strncmp(av[ac - 1], "0", 1) == 0)
	{
		printf("Philosophers don't need to eat\n");
		return (1);
	}
	init_data(&data, ac, av);
	init_semaphores(&data);
	start_routine(&data);
	kill_process(&data);
	return (0);
}
