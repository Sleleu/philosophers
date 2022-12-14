/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:25:56 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 13:20:28 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	end_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			free_stuff(table);
		i++;
	}
	if (pthread_join(table->control, NULL) != 0)
		free_stuff(table);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_destroy(&table->fork[i]) != 0)
			free_stuff(table);
		i++;
	}
	if (pthread_mutex_destroy(&table->print) != 0)
		free_stuff(table);
	if (pthread_mutex_destroy(&table->eat_check) != 0)
		free_stuff(table);
	free(table->philo);
	free(table->fork);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_parsing(argc, argv, &table);
	return (0);
}
