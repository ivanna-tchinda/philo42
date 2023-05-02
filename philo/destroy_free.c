#include "philo.h"

void destroy_free(t_data *data)
{
    int i;
    i = 0;
    while(i < data->nbphilos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->death);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->lock);
    free(data->forks);
    free(data->tid);
    free(data->philo);
}