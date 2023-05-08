/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:04:40 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 13:06:33 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*supervisor(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	i = 0;
	while (i < data->nbphilos)
	{
		sem_wait(data->full);
		i++;
	}
	sem_wait(data->print);
	printf("All philos have eaten!\n");
	sem_post(data->death);
	return (NULL);
}

void	*death(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		if (ft_timenow() - data->philo.time_last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			print_action(data, data->philo.id, "died 💀");
			sem_post(data->death);
			break ;
		}
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	int	i;

	i = -1;
	pthread_create(&data->supervisor, NULL, &supervisor, data);
	pthread_detach(data->supervisor);
	while (++i < data->nbphilos)
	{
		data->philo.id = i;
		data->philo_id[i] = fork();
		if (data->philo_id[i] == -1)
		{
			printf("process failed\n");
			return ;
		}
		if (data->philo_id[i] == 0)
		{
			init_philo(data);
			routine_func(data);
		}
	}
	sem_wait(data->death);
	return ;
}

void	routine_func(t_data *data)
{
	data->philo.time_last_meal = ft_timenow();
	pthread_create(&data->death_thread, NULL, &death, data);
	pthread_detach(data->death_thread);
	if (data->philo.id % 2 == 0)
		ft_usleep(data->philo.time_to_eat);
	while (1)
	{
		eating(data);
		if (data->nbphilos == 1)
			return ;
		sleep_think(data);
	}
}
