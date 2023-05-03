#include "philo_bonus.h"

void *check_death(void *args)
{
    t_data *data;

    data = (t_data *)args;
    while(1)
    {
        if(ft_timenow() - data->philo.time_of_last_meal > data->philo.time_to_die)
        {
            print_activity(data, data->philo.id, "died");
            sem_post(data->stop);
            exit(0);
            return(NULL);
        }
    }
    return(NULL);
}

void *philos_are_full(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    i = 0;
    while(i < data->nbphilos)
    {
        sem_wait(data->nbmeals);
        i++;
    }
    sem_wait(data->print);
    printf("All philos have eaten");
    return(NULL);
}


void meal_check(t_data *data)
{
    pthread_create(&data->is_dead, NULL, &philos_are_full, (void *)data);
    pthread_detach(data->is_dead);
}

void start_routine(t_data *data)
{
    int i;

    i = 0;
    data->start = ft_timenow();
    while(i < data->nbphilos)
    {
        data->philo_id = i;
        data->pid[i] = fork();
        if(data->pid[i] == -1)
        {
            while(i >= 0)
            {
                kill(data->pid[i], SIGKILL);
                i--;
            }
            return;
        }
        if(data->pid[i] == 0)
        {
            init_philo(data);
            routine(data);
        }
        i++;
    }
    sem_wait(data->stop);
    return;
}


void routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    data->start = ft_timenow();
    while(1)
    {
        eating(data);
        sleep_think(data);
    }
}

