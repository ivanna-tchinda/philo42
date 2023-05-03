#ifndef PHILO_H
#define PHILO_H

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
#include <signal.h>

struct s_data;

typedef struct s_philo{
    //INFOS
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_of_last_meal;
    int nb_of_meals;

    //T_DATA

    //THREADS
    pthread_t philo_id;

}               t_philo;

typedef struct s_data{
    //THREADS
    pthread_t is_dead;

    //INFOS
    int nbphilos;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    int nb_of_meals;
    int dead_id;
    int philo_id;
    long long start;

    //MUTEX
    sem_t *forks;
    sem_t *death;
    sem_t *nbmeals;
    sem_t *print;
    sem_t *stop;

    //PROCESS
    pid_t *pid;

    //PHILOS
    t_philo philo;
}               t_data;

//INIT
void init_data(t_data *data, int ac, char **av);
void init_mutex(t_data *data);
void init_philo(t_data *data);

//ROUTINE
void meal_check(t_data *data);
void *check_death(void *args);
void *philos_are_full(void *arg);
void start_routine(t_data *data);
void routine(void *arg);

//ACTIVITY
void eating(t_data *data);
void sleep_think(t_data *data);

//UTILS
void print_activity(t_data *data, int id, char *str);
void ft_usleep(int ms);
long int ft_timenow(void);

//DESTROY FREE
void kill_process(t_data *data);

#endif