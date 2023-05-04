#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>

struct s_data;

typedef struct s_philo{
  int id;
  int is_dead;
  int time_to_eat;
  int time_to_die;
  int time_to_sleep;
  unsigned long nb_of_meals;
  long long time_last_meal;
  int left_fork;
  int right_fork;
  int nbphilos;
  long long start_time;
  pthread_mutex_t print;
  struct s_data *data;
}              t_philo;

typedef struct s_data{

  t_philo *philo;
  int nbphilos;
  int time_to_eat;
  int time_to_die;
  int time_to_sleep;
  unsigned long nb_of_meals;
  int is_dead;
  pthread_mutex_t lock;
  pthread_mutex_t	*forks;
  pthread_t *tid;
  pthread_mutex_t print;
  pthread_mutex_t death;
  long long start;
}              t_data;

//INIT
void init_philo(t_data *data);
void init_data(t_data *data, int ac, char **av);
void init_mutex(t_data *data);

//ROUTINE
void start_routine(t_data *data);
void end_routine(t_data *data);
void *routine_func(void *arg);
void *supervisor(void *args);

//ACTIONS
void taking_forks(t_philo *philo);
void taking_forks2(t_philo *philo);
void death_philo(t_philo *philo, int i);
void eating(t_philo *philo);
void eating_else(t_philo *philo);
void release_forks(t_philo *philo);
void release_forks_else(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);

//UTILS
void print_action(t_data *data, int id, char *str);
void ft_usleep(int time, t_philo *philo);
long int ft_timenow(void);
int check_nb_meals(t_philo *philo);

//FREE
void destroy_free(t_data *data);
#endif