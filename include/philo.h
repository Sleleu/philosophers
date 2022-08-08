/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:39:11 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/08 20:56:09 by sleleu           ###   ########.fr       */
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
	int t_must_eat;
	pthread_t *philo;
	pthread_mutex_t *fork;
}	t_table;

typedef struct s_list
{
	struct s_list *next;
	struct s_list *prev;
}	t_list;

/* MAIN */

void*	routine();

/* PARSER */

int	ft_parsing(int argc, char **argv, t_table *table);

/* UTILS */

int	ft_atoi(const char *str);

#endif