/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:40:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/29 21:02:50 by sleleu           ###   ########.fr       */
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
	int last_eat;
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



/* PARSER */

void	ft_error(void);
void	ft_parsing(int argc, char **argv, t_table *table);

/* START PHILO */

time_t	get_time(t_table *table);
void	free_stuff(t_table *table, t_philo *philo);
void	ft_start_philo(t_table *table, t_philo *philo);

/* SIMULATION */

int		ft_is_dead(t_philo *philo);
void	time_to_eat(t_philo *philo);
void*	controller(void *arg);
void*	simulation(void *table);

/* UTILS */

int	ft_usleep(useconds_t useconds, t_philo *philo);
int	ft_atoi(const char *str);


#endif