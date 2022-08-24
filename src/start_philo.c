/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:18:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/23 18:42:01 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_stuff(t_table *table)
{
	free(table->philo);
	free(table->fork);
	ft_error();
}

void	ft_create_thread(t_table *table)
{
	int i;
	
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL) != 0)
			free_stuff(table);
		table->fork[i].free = 1;
		if (pthread_create(&table->philo[i].thread, NULL, simulation, (void *)table) != 0)
			free_stuff(table);
		table->philo[i].id = i + 1;
		printf("id des philos %d\n", table->philo[i].id);
		table->philo[i].alive = 1;
		table->philo[i].left_fork = 0;
		table->philo[i].right_fork = 0;
		i++;
	}
}

void	ft_join_thread(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->nb_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			free_stuff(table);
		i++;
	}
}

void	ft_set_table(t_table *table)
{
	ft_create_thread(table);
	ft_join_thread(table);
}