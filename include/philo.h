/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:40:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 20:14:43 by sleleu           ###   ########.fr       */
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
	int	left_fork;
	int	right_fork;
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
	pthread_t controller;
	struct timeval time;
	time_t current_time;
	time_t start_time;
}	t_table;

/* MAIN */

time_t	get_time(t_table *table);

/* PARSER */

void	ft_error(void);
void	ft_parsing(int argc, char **argv, t_table *table);

/* START PHILO */

void	free_stuff(t_table *table, t_philo **philo);
void	ft_start_philo(t_table *table, t_philo *philo);

/* SIMULATION */

void*	simulation(void *table);

/* UTILS */

int	ft_atoi(const char *str);


#endif