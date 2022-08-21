/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:39:11 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/21 20:45:08 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int nb_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int nb_eat;
	int	meal;
	struct s_philo *philo;
	struct s_fork *fork;
	pthread_t controller;
	struct timeval time;
	time_t current_time;
	time_t start_time;
}	t_table;

typedef struct s_philo
{
	int	id;
	int	alive;
	int right_fork;
	int left_fork;
	pthread_t thread;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t mutex;
	int	free;
}	t_fork;

/* MAIN */

time_t	get_time(t_table *table);

/* PARSER */

void	ft_error(void);
void	ft_parsing(int argc, char **argv, t_table *table);

/* SET_TABLE */

void	ft_set_table(t_table *table);

/* SIMULATION */

void*	simulation(void *table);

/* UTILS */

int	ft_atoi(const char *str);

#endif