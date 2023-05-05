#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
#include <sys/types.h>

struct t_data;

typedef struct s_philo{
  int id;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int nb_of_meals;
  int nbphilos;
  int start_time;
  struct s_data *data;
  long time_last_meal;
}              t_philo;

typedef struct s_data{
  int nbphilos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int nb_of_meals;
  long int start;
  pid_t *philo_id;
  pthread_t supervisor;
  pthread_t death_thread;
  sem_t *forks;
  sem_t *print;
  sem_t *full;
  sem_t *death;
  t_philo philo;
}              t_data;

void init_data(t_data *data, int ac, char **av);
void init_semaphores(t_data *data);
void init_philo(t_data *data);
void kill_process(t_data *data);
void *supervisor(void *args);
void start_routine(t_data *data);
void routine_func(t_data *data);
long int ft_timenow(void);
void print_action(t_data *data, int id, char *str);
void ft_usleep(int time, long time_of_last_meal, t_data *data);
void	free_tab(char **tab);
int	ft_atoi(const char *nptr);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void eating(t_data *data);
void sleep_think(t_data *data);

#endif