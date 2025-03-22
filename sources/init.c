/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:44:37 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:46:09 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

/**
 * @brief Function to initialize the mutexes
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
int	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	return (0);
}

/**
 * @brief Function to initialize the philosophers
 * @param data The data structure
 * @param argc The number of arguments
 * @param argv The arguments
 * @return 0 if success, 1/NULL if error
 */
int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meats_eaten = 0;
		data->philo[i].is_dead = 0;
		// data->philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		// data->philo[i].right_fork = malloc(sizeof(pthread_mutex_t));
		data->philo[i].eat = &data->eat;
		data->philo[i].write = &data->write;
		data->philo[i].dead = &data->dead;
		pthread_mutex_init(data->philo[i].left_fork, NULL);
		pthread_mutex_init(data->philo[i].right_fork, NULL);
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

/**
 * @brief Function to initialize the threads
 * @param data The data structure
 * @return 0 if success, 1/NULL if error
 */
int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->nb_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Function to initialize the program
 * @param data The data structure
 * @param argc The number of arguments
 * @param argv The arguments
 * @return 0 if success, 1/NULL if error
 */
int	init_program(t_data *data, int argc, char **argv)
{
	if (init_philos(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	if (init_threads(data))
		return (1);
	return (0);
}
