#include "philo_bonus.h"

void init_data(t_data *data, int ac, char **av)
{
    memset(data, 0, sizeof(t_data));
    data->nbphilos = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    data->dead_id = -1;
    data->pid = malloc(sizeof(pid_t) * data->nbphilos);
    if(ac == 6)
        data->nb_of_meals = atoi(av[5]);
    else
        data->nb_of_meals = -1;
    data->pid = malloc(sizeof(pid_t) * data->nbphilos);
    memset(data->pid, 0, sizeof(pid_t) * data->nbphilos);
}

void init_mutex(t_data *data)
{
    sem_unlink("forks");
    sem_unlink("death");
    sem_unlink("nb_of_meals");
    sem_unlink("print");
    sem_unlink("stop");
    
    data->forks = sem_open("forks",O_CREAT | O_EXCL, S_IRWXU, data->nbphilos);
    data->death = sem_open("death", O_CREAT | O_EXCL, S_IRWXU, 0);
    data->nbmeals = sem_open("nb_of_meals", O_CREAT | O_EXCL, S_IRWXU, 0);
    data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
    data->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
}

void init_philo(t_data *data)
{
    data->philo.time_of_last_meal = ft_timenow();
    pthread_create(&data->is_dead, NULL, &check_death, (void *)data);
    pthread_detach(data->is_dead);
}