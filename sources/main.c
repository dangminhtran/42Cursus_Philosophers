/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:13:51 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 14:33:57 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h" 

int main(int argc, char **argv)
{
    t_data data;
    t_philo philos[PHILO_MAX];
    pthread_mutex_t	forks[PHILO_MAX];

    if (argc < 5 || argc > 6)
    {
        write(2, "Error: Wrong number of arguments\n", 33);
        return (1);
    }
    if (check_args(argv) == 1)
        return (1);
    init_program(&data, philos);
    init_forks(forks, ft_atoi(argv[1]));
    init_philos(philos, &data, argv, forks);
    start_threads(&data);
    stop_program(&data, forks);
    return (0);
}
