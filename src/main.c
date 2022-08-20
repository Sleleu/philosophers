/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:33:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/21 00:22:46 by sleleu           ###   ########.fr       */
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

void	philo_eat(t_table *table)
{
	static int i = 0;
	pthread_mutex_lock(&table->fork[i]);
	usleep(table->t_eat);
	table->current_time = get_time(table);
	printf("[%ld] %d has taken a fork\n",table->current_time, i + 1);
	pthread_mutex_unlock(&table->fork[i]);
	i++;
}

void*	routine(t_table *table)
{
	static int i = 0;
	
	philo_eat(table);
	printf("Test from philo %d, nb = %d\n", (int)getpid(), i);
	printf("Ending threads\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table table;
	
	table.start_time = get_time(&table);
	
	ft_parsing(argc, argv, &table);
	free(table.philo);
	return (0);
}