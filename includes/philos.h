/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:07:30 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:21:43 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	// TODO - Utile ?
	int				meats_eaten;
	int				is_dead;
	int				nb_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_meals_to_eat;
	size_t			start_time;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;

}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;

}					t_data;

/* parsing.c */
int					check_is_number(char *arg);
int					check_arg_valid(char *arg);
int					check_args(char **argv);

/* init.c */
int					init_mutexes(t_data *data);
int					init_philos(t_data *data, int argc, char **argv);
int					init_program(t_data *data, int argc, char **argv);
int					init_threads(t_data *data);

/* routine.c */
void				*routine(void *philo);
void				eat(t_philo *philo);
void				sleep(t_philo *philo);
void				think(t_philo *philo);

/* check.c */
int					check_dead(t_philo *philo);
int					check_eating(t_philo *philo);
int					check_meals(t_philo *philo);

/* philos.c */
int					detroy_threads(t_data *data);
void				destroy_mutexes(t_data *data);
int					stop_program(t_data *data);
int					start_threads(t_data *data);

/* EXTRAS */
int					ft_atoi(char *str);
int					get_time(void);

#endif