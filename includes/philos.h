/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:07:30 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/22 16:46:20 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <../extras/extras.h>
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
	int			meats_eaten;
	int				nb_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_meals_to_eat;
	size_t			start_time;
	size_t			last_meal;
	int				*is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;

}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	// pthread_mutex_t	forks[PHILO_MAX];
	int	is_dead;
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
void	init_philos(t_philo *philos, t_data *data, char **argv, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, int philo_num);
int	init_program(t_data *data, t_philo *philos);

/* routine.c */ 
void				is_eating(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				is_thinking(t_philo *philo);
void				print_message(char *message, t_philo *philo, int id);
void				*routine(void *arg);

/* check.c */
int check_philosopher_death(t_philo *philos);
int check_have_eaten(t_philo *philos);
void *monitor_philosophers(void *arg);

/* philos.c */
void				destroy_mutexes(t_data *data);
int stop_program(t_data *data, pthread_mutex_t *forks);
int					start_threads(t_data *data);
// int	detroy_threads(t_data *data);

#endif