/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:52:40 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:53:02 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("full");
	sem_unlink("death");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, data->nbphilos);
	data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->full = sem_open("full", O_CREAT | O_EXCL, S_IRWXU, 0);
	data->death = sem_open("death", O_CREAT | O_EXCL, S_IRWXU, 0);
}

void	init_philo(t_data *data)
{
	data->philo.time_to_die = data->time_to_die;
	data->philo.time_to_eat = data->time_to_eat;
	data->philo.time_to_sleep = data->time_to_sleep;
	data->philo.nb_of_meals = 0;
	data->philo.nbphilos = data->nbphilos;
	data->philo.data = data;
	data->philo.time_last_meal = ft_timenow();
}

void	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nbphilos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start = ft_timenow();
	data->philo_id = malloc(sizeof(pid_t) * data->nbphilos);
	memset(data->philo_id, 0, sizeof(pid_t) * data->nbphilos);
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	else
		data->nb_of_meals = -1;
}
