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

    if (argc < 5 || argc > 6)
    {
        write(2, "Error: Wrong number of arguments\n", 33);
        return (1);
    }
    if (check_args(argv))
        return (1);
    data.philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
    data.philo->nb_philos = ft_atoi(argv[1]);
    data.philo->time_to_die = ft_atoi(argv[2]);
    data.philo->time_to_eat = ft_atoi(argv[3]);
    data.philo->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data.philo->nb_meals_to_eat = ft_atoi(argv[5]);
    else
        data.philo->nb_meals_to_eat = -1;
    data.philo->start_time = get_time();
    if (init_program(&data, argc, argv))
        return (1);
    return (0);
}