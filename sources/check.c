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

/**
 * @brief Function to check if the philosopher is dead
 * @param philo The philosopher
 * @return 0 if success, 1 if error
 */
int	check_dead(t_philo *philo)
{
    if (philo->nb_meals_to_eat == 0)
    {
        pthread_mutex_lock(philo->dead);
        philo->is_dead = 1;
        pthread_mutex_unlock(philo->dead);
        return (1);
    }
    if (get_time() - philo->last_meal > philo->time_to_die)
    {
        pthread_mutex_lock(philo->dead);
        philo->is_dead = 1;
        pthread_mutex_unlock(philo->dead);
        return (1);
    }
    return (0);
}

/**
 * @brief Function to check if the philosopher is eating
 * @param philo The philosopher
 * @return 0 if success, 1 if error
 */
int	check_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->eat);
    if (get_time() - philo->last_meal > philo->time_to_eat)
    {
        philo->meats_eaten++;
        philo->nb_meals_to_eat--;
        pthread_mutex_unlock(philo->eat);
        return (1);
    }
    pthread_mutex_unlock(philo->eat);
    return (0);
}

/**
 * @brief Function that check if the number of meals to eat is reached
 * @param philo The philosopher
 * @return 0 if success, 1 if error
 */
int	check_meals(t_philo *philo)
{
    if (philo->nb_meals_to_eat == 0)
        return (1);
    return (0);
}