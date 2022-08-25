/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:38:53 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 20:15:16 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_stuff(t_table *table, t_philo **philo)
{
	free(philo);
	free(table->fork);
	ft_error();
}

void	ft_start_philo(t_table *table, t_philo *philo)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	j = 0;
	k = 0;
	printf("nb philo : %d\n", table->nb_philo);
	while (j < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[j], NULL) != 0)
			free_stuff(table, &philo);
		j++;
	}
	while (i < table->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]) != 0)
			free_stuff(table, &philo);
		i++;
	}
	while (k < table->nb_philo)
	{
		if (pthread_join(philo[k].thread, NULL) != 0)
			free_stuff(table, &philo);
		k++;
	}
}