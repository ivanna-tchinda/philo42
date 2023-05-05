#include "philo_bonus.h"

void kill_process(t_data *data)
{
    int i;

    i = 0;
    while(i < data->nbphilos)
    {
        kill(data->philo_id[i] , SIGKILL);
        i++;
    }
    sem_close(data->death);
    sem_close(data->forks);
    sem_close(data->print);
    sem_close(data->full);
    free(data->philo_id);
}