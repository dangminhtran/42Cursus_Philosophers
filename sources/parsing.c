/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:06:58 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 15:45:49 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int check_is_number(char *arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        if (arg[i] < '0' || arg[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int check_arg_valid(char *arg)
{
    if (check_is_number(arg))
        return (1);
    if (ft_atoi(arg) < 0)
        return (1);
    return (0);
}

int check_args(char **argv)
{
    int num_philos = ft_atoi(argv[1]);
    int time_to_die = ft_atoi(argv[2]);
    int time_to_eat = ft_atoi(argv[3]);
    int time_to_sleep = ft_atoi(argv[4]);

    if (check_arg_valid(argv[1]) || num_philos <= 0 || num_philos > PHILO_MAX)
        return(write(2, "Error: Number of philosophers must be a positive integer\n", 58), 1);
    if (check_arg_valid(argv[2]) || time_to_die <= 0)
        return(write(2, "Error: Time to die must be a positive integer\n", 46), 1);
    if (check_arg_valid(argv[3]) || time_to_eat <= 0)
        return(write(2, "Error: Time to eat must be a positive integer\n", 47), 1);
    if (check_arg_valid(argv[4]) || time_to_sleep <= 0)
        return(write(2, "Error: Time to sleep must be a positive integer\n", 49), 1);
    
    if (argv[5])
    {
        if (check_arg_valid(argv[5]) || ft_atoi(argv[5]) <= 0)
            return (write(2, "Error: Number of meals must be a positive integer\n", 51), 1);
    }
    return (0);
}
