/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:38:53 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 12:27:33 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	free_stuff(t_table *table)
{
	free(table->philo);
	free(table->fork);
	ft_error();
}

void	ft_start_mutex(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			free_stuff(table);
		i++;
	}
	if (pthread_mutex_init(&table->eat_check, NULL) != 0)
		free_stuff(table);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		free_stuff(table);
}

void	ft_start_philo(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	ft_start_mutex(table, philo);
	table->start_time = get_time();
	if (pthread_create(&table->control, NULL, controller, table) != 0)
		free_stuff(table);
	while (i < table->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]) != 0)
			free_stuff(table);
		pthread_mutex_lock(&table->eat_check);
		philo[i].last_eat = get_time();
		pthread_mutex_unlock(&table->eat_check);
		i++;
	}
	end_philo(table);
}
