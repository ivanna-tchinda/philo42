/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:41:57 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:47:51 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_func(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	philo->start_time = ft_timenow();
	philo->time_last_meal = ft_timenow();
	if (philo->id % 2 == 0)
		ft_usleep(20, data);
	while (data->dead == false && data->full == false)
	{
		eating(philo);
		if (data->dead == false || data->full == false)
			sleeping(philo);
		if (data->dead == false || data->full == false)
			thinking(philo);
	}
	return (NULL);
}

void	*death_philo(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	i = 0;
	while (1)
	{
		i = -1;
		while (++i < data->nbphilos)
		{
			if (ft_timenow() - data->philo[i].time_last_meal > data->time_to_die
				&& data->full == false)
			{
				pthread_mutex_lock(&data->print);
				if (data->nbphilos == 1)
					pthread_mutex_unlock
						(&data->forks[data->philo[i].left_fork]);
				print_action(data, i, "died 💀");
				data->dead = true;
				pthread_mutex_unlock(&data->print);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	pthread_t	*thread_id;
	int			i;
	int			status;

	i = 0;
	status = 0;
	thread_id = malloc(sizeof(pthread_t) * data->nbphilos);
	data->start = ft_timenow();
	pthread_create(&data->thread2, NULL, death_philo, data);
	pthread_detach(data->thread2);
	while (i < data->nbphilos)
	{
		if (pthread_create
			(&thread_id[i], NULL, &routine_func, &data->philo[i]) != 0)
		{
			status = write(1, "failed to create\n", 14);
			return ;
		}
		i++;
	}
	data->tid = thread_id;
	return ;
}

void	end_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbphilos)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
}
