/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:50:23 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/22 23:03:07 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	time_to_eat(t_table *table, int i)
{
	if (table->fork[i].free == 1)
	{
		pthread_mutex_lock(&table->fork[i].mutex);
		table->fork[i].free = 0;
		table->philo[i - 1].right_fork = 1;
		printf("[%ld] %d has taken a fork\n", table->current_time, table->philo[i].id);
	}
	if (table->fork[i - 1].free == 1)
	{
		pthread_mutex_lock(&table->fork[i - 1].mutex);
		table->fork[i].free = 0;
		table->philo[i - 1].left_fork = 1;
		printf("[%ld] %d has taken a fork\n", table->current_time, table->philo[i].id);
	}
	usleep(100);
	if (table->philo[i - 1].left_fork == 1 && table->philo[i - 1].right_fork == 1)
	{
		printf("[%ld] %d is eating\n", table->current_time, table->philo[i].id);
		usleep(table->time_eat);
		table->current_time = get_time(table);
		
		table->fork[i].free = 1;
		table->fork[i - 1].free = 1;
		pthread_mutex_unlock(&table->fork[i].mutex);
		pthread_mutex_unlock(&table->fork[i - 1].mutex);
	}
}

void*	simulation(void *arg)
{
	t_table *table;

	table = (t_table *)arg;
	int i = 0;
	while (42)
	{
		time_to_eat(table, table->philo[i].id);
		i++;
		if (i >= table->nb_philo)
			i = 0;
	}
	return (NULL);
}