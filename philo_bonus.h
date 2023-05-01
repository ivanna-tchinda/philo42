#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <semaphore.h>
#include <fcntl.h> 

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
  pthread_t tid;
  long long start;
  sem_t *forks;
  sem_t *print;
  sem_t *lock;
}              t_data;

//PARSING
int ft_parse(int ac, char **av);

//INIT
void init_data(t_data *data, int ac, char **av);
void init_philo(t_data *data);
void init_sem(t_data *data);

//UTILS
int check_nb_meals(t_philo *philo);
void print_action(t_data *data, int id, char *str);
void ft_usleep(int time, t_philo *philo);
long int ft_timenow(void);

//ROUTINE
void start_routine(t_data *data);

//DESTROY&FREE
void destroy_free(t_data *data);

//ACTIVITY
void eating(t_philo *philo);
void release_forks(t_data *data);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);

#endif