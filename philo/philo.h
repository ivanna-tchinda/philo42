/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:13:18 by itchinda          #+#    #+#             */
/*   Updated: 2023/05/08 12:40:40 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_philo{
	unsigned long	nb_of_meals;
	long long		start_time;
	long long		time_last_meal;
	int				id;
	int				is_dead;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				left_fork;
	int				right_fork;
	int				nbphilos;
	struct s_data	*data;
}		t_philo;

typedef struct s_data{
	unsigned long	nb_of_meals;
	long long		start;
	int				nbphilos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				is_dead;
	int				is_full;
	int				belly;
	bool			dead;
	bool			full;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_t		*tid;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		thread2;
	t_philo			*philo;
}		t_data;

long int	ft_timenow(void);
void		init_philo(t_data *data);
void		init_data(t_data *data, int ac, char **av);
void		init_mutex(t_data *data);
void		start_routine(t_data *data);
void		end_routine(t_data *data);
void		*routine_func(void *arg);
void		*supervisor(void *args);
void		taking_forks(t_philo *philo);
void		taking_forks2(t_philo *philo);
void		*death_philo(void *args);
void		eating(t_philo *philo);
void		eating_suite(t_philo *philo);
void		eating_else(t_philo *philo);
void		release_forks(t_philo *philo);
void		release_forks_else(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		print_action(t_data *data, int id, char *str);
void		ft_usleep(int time, t_data *data);
int			check_nb_meals(t_philo *philo);
int			ft_atoi(const char *nptr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
void		destroy_free(t_data *data);
#endif
