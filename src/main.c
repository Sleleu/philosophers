/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:25:56 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 19:52:01 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time(t_table *table)
{
	static int i = 0;

	gettimeofday(&table->time, NULL);
	if (i != 0)
	{
		table->current_time = (table->time.tv_sec * 1000) + (table->time.tv_usec / 1000);
		return (table->current_time -= table->start_time);
	}
	i++;
		return (table->time.tv_sec * 1000) + (table->time.tv_usec / 1000);
}

// int	main(int argc, char **argv)
// {
// 	t_table table;
// 	t_philo **philo;
// 	philo = malloc (sizeof(t_philo *)*ft_atoi(argv[1]));
// 	ft_parsing(argc, argv, &table, philo);
// 	ft_start_philo(&table, philo);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_table table;

	ft_parsing(argc, argv, &table);
	return (0);
}