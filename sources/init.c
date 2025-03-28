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

int	init_mutexes(t_data *data)
{
    // int i;

    // i = 0;
    
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->dead, NULL);

    // while (i < data->philos->nb_philos)
    // {
    //     if (pthread_mutex_init(&forks[i], NULL) != 0)
    //     {
    //         write(2, "Error: Mutex init failed\n", 25);
    //         return (1);
    //     }
    //     i++;
    // }
	return (0);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, t_data *data, char **argv, pthread_mutex_t *forks)
{
    int	i;

    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        philos[i].id = i + 1;
        philos[i].meats_eaten = 0;
        philos[i].nb_philos = ft_atoi(argv[1]);
        philos[i].time_to_die = ft_atoi(argv[2]);
        philos[i].time_to_eat = ft_atoi(argv[3]);
        philos[i].time_to_sleep = ft_atoi(argv[4]);
        if (argv[5])
            philos[i].nb_meals_to_eat = ft_atoi(argv[5]);
        else
            philos[i].nb_meals_to_eat = -1;
        philos[i].start_time = get_time();
        philos[i].last_meal = get_time();
        philos[i].left_fork = &forks[i];
        if (i == 0)
            philos[i].right_fork = &forks[philos[i].nb_philos - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        philos[i].is_dead = &data->is_dead;
        philos[i].write = &data->write;
        philos[i].eat = &data->eat;
        philos[i].dead = &data->dead;   
        i++;
    }
}

int	init_program(t_data *data, t_philo *philos)
{
    data->is_dead = 0;
    data->philos = philos;
	if (init_mutexes(data))
		return (1);
	return (0);
}
