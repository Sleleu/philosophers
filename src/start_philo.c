/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:38:53 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/30 07:17:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time(t_table *table)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	free_stuff(t_table *table, t_philo *philo)
{
	free(philo);
	free(table->fork);
	ft_error();
}

void	ft_start_philo(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	table->start_time = get_time(table);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			free_stuff(table, philo);
		if (pthread_mutex_init(&philo[i].died, NULL) != 0)
			free_stuff(table, philo);
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
		free_stuff(table, philo);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]) != 0
			|| pthread_create(&table->control, NULL, controller, table) != 0)
			free_stuff(table, philo);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			free_stuff(table, philo);
		i++;
	}
}
