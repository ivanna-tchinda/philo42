#include "philo_bonus.h"

void kill_process(t_data *data)
{
    int i;

    i = 0;
    while(i < data->nbphilos)
    {
        kill(data->pid[i] , SIGKILL);
        i++;
    }
}