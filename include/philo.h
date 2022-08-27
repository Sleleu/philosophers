/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:40:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/27 03:15:08 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	id;
	int	alive;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t died;
	int got_l_fork;
	int	got_r_fork;
	pthread_t	thread;
	struct s_table *table;
}	t_philo;

typedef struct s_table
{
	int	nb_philo;
	int	time_die;
	int time_eat;
	int	time_sleep;
	int	nb_eat;
	pthread_mutex_t *fork;
	pthread_t control;
	struct timeval time;
	time_t current_time;
	time_t start_time;
	t_philo *philo;
}	t_table;

/* MAIN */



/* PARSER */

void	ft_error(void);
void	ft_parsing(int argc, char **argv, t_table *table);

/* START PHILO */

time_t	get_time(t_table *table);
void	free_stuff(t_table *table, t_philo *philo);
void	ft_start_philo(t_table *table, t_philo *philo);

/* SIMULATION */

void	time_to_eat(t_philo *philo);
void*	controller(void *arg);
void*	simulation(void *table);

/* UTILS */

int	ft_atoi(const char *str);


#endif