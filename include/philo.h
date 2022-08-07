/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:39:11 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/07 18:40:34 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_table
{
	int nb_philo;
	pthread_t *philo;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
}	t_table;

/* MAIN */

void*	routine();

/* PARSER */

int	ft_parsing(char **argv, t_table *table);

/* UTILS */

int	ft_atoi(const char *str);

#endif