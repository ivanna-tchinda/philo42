/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:59:00 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:04:27 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int					i;
	pthread_mutex_t		*mutex;

	i = 0;
	mutex = malloc(sizeof (pthread_mutex_t) * data->nbphilos);
	while (i < data->nbphilos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->forks = mutex;
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->nbphilos);
	if (!philo)
		return ;
	memset(philo, 0, data->nbphilos);
	i = 0;
	while (i < data->nbphilos)
	{
		philo[i].id = i;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].nb_of_meals = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->nbphilos;
		philo[i].nbphilos = data->nbphilos;
		philo[i].data = data;
		philo[i].time_last_meal = ft_timenow();
		philo[i].is_dead = 0;
		i++;
	}
	data->philo = philo;
}

void	init_data(t_data *data, int ac, char **av)
{
	data->nbphilos = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->is_dead = 0;
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	else
		data->nb_of_meals = -1;
	data->is_full = data->nb_of_meals * data->nbphilos;
	data->belly = 0;
	data->dead = false;
	data->full = false;
}
