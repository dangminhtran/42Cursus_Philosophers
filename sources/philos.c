/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:06:08 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 15:23:37 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/**
 * @brief Function to destroy the threads
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
int	detroy_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->nb_philos)
	{
		pthread_mutex_destroy(data->philo[i].left_fork);
		pthread_mutex_destroy(data->philo[i].right_fork);
		i++;
	}
	return (0);
}

/**
 * @brief Function to destroy the mutexes
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
}

/**
 * @brief Function to stop the program
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
int	stop_program(t_data *data)
{
	detroy_threads(data);
	destroy_mutexes(data);
	free(data->philo);
	return (0);
}

/**
 * @brief Function to start the threads
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
int	start_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo->nb_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo->nb_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
