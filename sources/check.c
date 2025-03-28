/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:10:40 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:14:53 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int check_philosopher_death(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].nb_philos)
    {
        pthread_mutex_lock(philos[i].eat);
        if (get_time() - philos[i].last_meal >= philos[i].time_to_die)
        {
            pthread_mutex_unlock(philos[i].eat);
            print_message("died", &philos[i], philos[i].id);
            
            pthread_mutex_lock(philos[0].dead);
            *philos[0].is_dead = 1;
            pthread_mutex_unlock(philos[0].dead);
            
            return (1);
        }
        pthread_mutex_unlock(philos[i].eat);
        i++;
    }
    return (0);
}

int check_have_eaten(t_philo *philos)
{
    int i;
    int all_satisfied;

    i = 0;
    all_satisfied = 0;

    if (philos[0].nb_meals_to_eat == -1)
        return (0);

    while (i < philos[0].nb_philos)
    {
        pthread_mutex_lock(philos[i].eat);
        if (philos[i].meats_eaten >= philos[i].nb_meals_to_eat)
            all_satisfied++;
        pthread_mutex_unlock(philos[i].eat);
        i++;
    }

    if (all_satisfied == philos[0].nb_philos)
    {
        pthread_mutex_lock(philos[0].dead);
        *philos->is_dead = 1;
        pthread_mutex_unlock(philos[0].dead);
        return (1);
    }
    return (0);
}

void *monitor_philosophers(void *arg)
{
    t_philo *philos;
    
    philos = (t_philo *)arg;

    while (1)
    {
        if (check_philosopher_death(philos) || check_have_eaten(philos))
        {
            pthread_mutex_lock(philos[0].dead);
            *philos->is_dead = 1;
            pthread_mutex_unlock(philos[0].dead);
            break;
        }
        usleep(1000);
    }
    return (arg);
}