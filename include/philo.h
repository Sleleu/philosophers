/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:40:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 09:12:09 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_philo
{
	int	id;
	int	alive;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t eat_check;
	int got_l_fork;
	int	got_r_fork;
	time_t last_eat;
	pthread_t	thread;
	struct s_table *table;
}	t_philo;

typedef struct s_table
{
	int	nb_philo;
	int	time_die;
	int time_eat;
	int	time_sleep;
	int died;
	int	nb_eat;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	pthread_t control;
	time_t start_time;
	t_philo *philo;
}	t_table;

/* MAIN */

void end_philo(t_table *table);

/* PARSER */

void	ft_error(void);
void	ft_parsing(int argc, char **argv, t_table *table);

/* START PHILO */

time_t	get_time(void);
void	free_stuff(t_table *table);
void	ft_start_philo(t_table *table, t_philo *philo);

/* SIMULATION */

int		ft_is_dead(t_philo *philo);
void	time_to_eat(t_philo *philo);
void*	controller(void *arg);
void*	simulation(void *table);

/* UTILS */

void	ft_print(t_philo *philo, int print);
int	ft_atoi(const char *str);


#endif