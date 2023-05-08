/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:09:45 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:12:27 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (!(av[i][j] <= 57 && av[i][j] >= 48))
			{
				printf("Enter 5 or 6 digits superior to 0\n");
				return (1);
			}
			j++;
		}
		if (ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
		{
			printf("Enter only integers superior to 0\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Enter 5 or 6 digits\n");
		return (0);
	}
	if (ft_strncmp(av[ac - 1], "0", 1) == 0)
	{
		printf("Philosophers don't need to eat\n");
		return (0);
	}
	if (ft_parse(ac, av) == 1)
		return (0);
	init_data(&data, ac, av);
	init_mutex(&data);
	init_philo(&data);
	start_routine(&data);
	end_routine(&data);
	destroy_free(&data);
	exit(0);
	return (0);
}
