/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:48 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:09:23 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbphilos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	free(data->forks);
	free(data->tid);
	free(data->philo);
}
