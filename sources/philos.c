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

int	detroy_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos->nb_philos)
	{
		pthread_mutex_destroy(data->philos[i].left_fork);
		pthread_mutex_destroy(data->philos[i].right_fork);
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
}

int stop_program(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->philos->nb_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    detroy_threads(data);
    destroy_mutexes(data);
    return (0);
}


int start_threads(t_data *data)
{
    pthread_t monitor_thread;
    int i;

    i = 0;
    
    if (pthread_create(&monitor_thread, NULL, monitor_philosophers, data->philos) != 0)
    {
        write(2, "Error: Monitor thread creation failed\n", 38);
        return (1);
    }

    while (i < data->philos[0].nb_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
        {
            write(2, "Error: Philosopher thread creation failed\n", 42);
            return (1);
        }
        i++;
    }
    i = 0;
    if (pthread_join(monitor_thread, NULL) != 0)
    {
        write(2, "Error: Monitor thread join failed\n", 34);
        return (1);
    }
    while (i < data->philos[0].nb_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
        {
            write(2, "Error: Thread join failed\n", 26);
            return (1);
        }
        i++;
    }
    return (0);
}
