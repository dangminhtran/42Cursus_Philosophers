/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:46:37 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:26:31 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/**
 * @brief Function to print a message
 * @param message The message
 * @param philo The philosopher
 * @param id The id of the philosopher
 * @return void
 */
void   print_message(char *message, t_philo *philo, int id)
{
    pthread_mutex_lock(philo->write);
    printf("%ld %d %s\n", get_time() - philo->start_time, id + 1, message);
    pthread_mutex_unlock(philo->write);
}

/**
 * @brief Function to make the philosopher eat
 * @param philo The philosopher
 * @return void
 */
void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a right fork", philo, philo->id);
	if (philo->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		print_message("died", philo, philo->id);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a left fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = get_time();
	philo->meats_eaten++;
	philo->nb_meals_to_eat--;
	pthread_mutex_unlock(philo->eat);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/**
 * @brief Function to make the philosopher sleep
 * @param philo The philosopher
 * @return void
 */
void	sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id
		+ 1);
	usleep(philo->time_to_sleep * 1000);
}

/**
 * @brief Function to make the philosopher think
 * @param philo The philosopher
 * @return void
 */
void	think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id
		+ 1);
}

/**
 * @brief Function to make the philosopher routine
 * @param philo The philosopher
 * @return void
 */
void	*routine(void *philo)
{
	t_philo	*philo;

	philo = (t_philo *)philo;
	while (1)
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (NULL);
}
