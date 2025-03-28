/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:46:37 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:44:15 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void print_message(char *message, t_philo *philo, int id)
{
    pthread_mutex_lock(philo->dead);
    if (*philo->is_dead == 1)
    {
        pthread_mutex_unlock(philo->dead);
        return;
    }
    pthread_mutex_unlock(philo->dead);

    pthread_mutex_lock(philo->write);
    printf("%ld %d %s\n", get_time() - philo->start_time, id, message);
    pthread_mutex_unlock(philo->write);
}

void is_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_message("has taken a right fork", philo, philo->id);
    if (philo->nb_philos == 1)
    {
        usleep(philo->time_to_die * 1000);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_lock(philo->left_fork);
    print_message("has taken a left fork", philo, philo->id);
    print_message("is eating", philo, philo->id);
    pthread_mutex_lock(philo->eat);
    philo->last_meal = get_time();
    philo->meats_eaten++;
    pthread_mutex_unlock(philo->eat);
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void is_sleeping(t_philo *philo)
{
    print_message("is sleeping", philo, philo->id);
    usleep(philo->time_to_sleep * 1000);
}

void is_thinking(t_philo *philo)
{
    print_message("is thinking", philo, philo->id);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(philo->time_to_eat * 500);
    while (1)
    {
        pthread_mutex_lock(philo->dead);
        if (*philo->is_dead == 1)
        {
            pthread_mutex_unlock(philo->dead);
            break;
        }
        pthread_mutex_unlock(philo->dead);
        is_eating(philo);
        is_sleeping(philo);
        is_thinking(philo);
    }
    return NULL;
}
