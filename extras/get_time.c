/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:18:19 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 15:41:39 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"

size_t get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (size_t)(time.tv_sec * 1000 + (time.tv_usec / 1000));
}
