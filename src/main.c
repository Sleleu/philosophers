/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:33:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/21 16:54:37 by sleleu           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_table table;
	
	table.start_time = get_time(&table);
	ft_parsing(argc, argv, &table);
	ft_set_table(&table);
	free(table.philo);
	return (0);
}