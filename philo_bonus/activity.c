#include "philo_bonus.h"

void eating(t_data *data)
{
    //TAKE FORKS
    sem_wait(data->forks);
    sem_wait(data->forks);

    //PRINT
    sem_wait(data->print);
    print_activity(data, data->philo_id, "has taken a fork 🍴");
    print_activity(data, data->philo_id, "has taken a fork 🍴");
    print_activity(data, data->philo_id, "is eating 🍚");
    sem_post(data->print);
    data->philo.time_of_last_meal = ft_timenow();

    //EAT
    data->philo.nb_of_meals += 1;
    //if(philo->nb_of_meals == data->nb_of_meals)
      //  sem_post(data->nbmeals);

    //RELEASE_FORKS
    ft_usleep(data->philo.time_to_eat);
    sem_post(data->forks);
    sem_post(data->forks);
}

void sleep_think(t_data *data)
{

    //SLEEP
    sem_wait(data->print);
    print_activity(data, data->philo_id, "is sleeping 💤");
    sem_post(data->print);
    ft_usleep(data->time_to_sleep);

    //THINK
    sem_wait(data->print);
    print_activity(data, data->philo_id, "is thinking 🤔");
    sem_post(data->print);
}