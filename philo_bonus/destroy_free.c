#include "philo_bonus.h"

void free_data(t_data *data)
{
    free(data->philo_id);
    sem_close(data->print);
    sem_close(data->forks);
    sem_close(data->full);
    sem_close(data->death);
    return;
}

void kill_process(t_data *data)
{
    int i = -1;
    while(++i < data->nbphilos)
        sem_wait(data->death);
    i = -1;
    while(++i < data->nbphilos)
        kill(data->philo_id[i], SIGKILL);
    return;
}