/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:39:11 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/21 00:12:50 by sleleu           ###   ########.fr       */
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
	int t_die;
	int t_eat;
	int t_sleep;
	int nb_eat;
	int	meal;
	pthread_t *philo;
	pthread_mutex_t *fork;
	struct timeval time;
	time_t current_time;
	time_t start_time;
}	t_table;


/* MAIN */

void*	routine();

/* PARSER */

int	ft_parsing(int argc, char **argv, t_table *table);

/* UTILS */

int	ft_atoi(const char *str);

#endif