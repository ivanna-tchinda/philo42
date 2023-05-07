#include "philo_bonus.h"

void free_data(t_data *data)
{
    free(data->philo_id);
    // sem_post(data->print);
    sem_close(data->print);
    sem_close(data->forks);
    sem_close(data->full);
    sem_close(data->death);
    return;
}

void kill_process(t_data *data)
{
    int i = 0;
    printf("waiting for death\n");
    // printf("pid %d, %d %d %d %d\n", getpid(), data->philo_id[0], data->philo_id[1], data->philo_id[2], data->philo_id[3]);
    // sem_post(data->death);
    while(i < data->nbphilos)
    {
        kill(data->philo_id[i], SIGKILL);
        printf("kill\n");
        i++;
    }
<<<<<<< HEAD
    free_data(data);
    // i = 0;
    // while(i < data->nbphilos)
    // sem_wait(data->death);
    return;
=======
    sem_close(data->death);
    sem_close(data->forks);
    sem_close(data->print);
    sem_close(data->full);
    free(data->philo_id);
>>>>>>> ee0dc411f70c95adedb6f1a9f336ec6b534131e2
}