
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


typedef struct t_currentphilo
{
    int is_dead;
    struct t_philo *data;

}               s_currentphilo;

typedef struct t_philo
{
    s_currentphilo *current_phil;
    pthread_t thread_id;
    long int begin_time;
    long int eat_time;
    int curr_phil;
    pthread_mutex_t *forks;
    pthread_mutex_t lock;
    int numphilos;
    int is_dead;
    int id;
    float time_to_die;
    float time_to_eat;
    float time_to_sleep;
    int many_times_to_eat;
    struct timeval current_time;

}               s_philo;

typedef struct t_data{
  s_philo *philo;
  s_currentphilo info;
}              s_data;

//MAIN
void *init_threads(s_philo *philo, char **av);
void *routine_func(void *arg);
void *start_routine(s_philo *philo);
long int ft_timenow(void);
void ft_usleep(float time);
void *destroy_mutex(s_philo *philo);
void *init_mutex(s_philo *philo);
void print_activity(int id, char *activity, s_philo *philo);
void free_philo(s_philo *philo);
void check_all_ate(s_philo *philo, int eat);


//EATING
void *taking_forks2(s_philo *philo);
void *taking_forks(s_philo *philo);
void *eating_routine(s_philo *philo);

void *take_forks(s_philo philo);


//SLEEP
void *sleeping_routine(s_philo *philo);
void *sleeping(void *ptr);

//THINK
void *thinking(void *ptr);
void *thinking_routine(s_philo *philo);

// UTILS
int	ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif