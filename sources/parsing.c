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

/**
 * @brief Function to check if the argument is a number
 * @param arg The argument
 * @return 0 if success, 1 if error
 */
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

/**
 * @brief Function to check if the argument is valid
 * @param arg The argument
 * @return 0 if success, 1 if error
 */
int check_arg_valid(char *arg)
{
    if (check_is_number(arg))
        return (1);
    if (atoi(arg) < 0)
        return (1);
    return (0);
}

/**
 * @brief Function to check if the arguments are valid
 * @param argv The arguments
 * @return 0 if success, 1 if error
 */
int check_args(char **argv)
{
    if (check_arg_valid(argv[1]) && argv[1] <= 0)
        return(write(2, "Error: Number of philosophers must be a positive integer\n", 58), 1);
    if (check_arg_valid(argv[2]) && argv[2] <= 0)
        return(write(2, "Error: Time to die must be a positive integer\n", 46), 1);
    if (check_arg_valid(argv[3]) && argv[3] <= 0)
        return(write(2, "Error: Time to eat must be a positive integer\n", 47), 1);
    if (check_arg_valid(argv[4]) && argv[4] <= 0)
        return(write(2, "Error: Time to sleep must be a positive integer\n", 49), 1);
    if (argv[5] && (check_arg_valid(argv[5]) && argv[5] <= 0))
        return(write(2, "Error: Number of meals must be a positive integer\n", 51), 1);
    return (0);
}

