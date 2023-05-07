#include "philo_bonus.h"

void free_data(t_data *data)
{
    // sem_post(data->print);
    free(data->philo_id);
    sem_close(data->print);
    sem_close(data->forks);
    sem_close(data->full);
    sem_close(data->death);
    return;
}

void kill_process(t_data *data)
{
    int i = 0;
    // printf("pid %d, %d %d %d %d\n", getpid(), data->philo_id[0], data->philo_id[1], data->philo_id[2], data->philo_id[3]);
    // sem_post(data->death);
    printf("waiting for death\n");
    while(i < data->nbphilos)
    {
        sem_wait(data->death);
        i++;
    }
    i = 0;
    while(i < data->nbphilos)
    {
        kill(data->philo_id[i], SIGKILL);
        printf("kill\n");
        i++;
    }
    // sem_close(data->death);
    // sem_close(data->forks);
    // sem_close(data->print);
    // sem_close(data->full);
    // free(data->philo_id);
    return;
}