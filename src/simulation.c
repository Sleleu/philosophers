/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/30 06:03:42 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d is thinking\n", get_time(philo->table) - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(100);
}

void	get_some_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d is sleeping\n", get_time(philo->table) - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->time_sleep * 1000);
}

void	odd_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo->got_l_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(philo->r_fork);
	philo->got_r_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

void	even_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo->got_r_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(philo->l_fork);
	philo->got_l_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

void	eat(t_philo *philo)
{	
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
		printf("[%ld] %d is eating\n", get_time(philo->table) - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->time_eat * 1000);
	pthread_mutex_lock(&philo->died);
	philo->last_eat = get_time(philo->table);
	pthread_mutex_unlock(&philo->died);
	philo->got_l_fork = 0;
	philo->got_r_fork = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	get_some_sleep(philo);
}

void*	controller(void *arg)
{
	t_table *table;
	int	i;

	table = (t_table *)arg;
	i = 0;
	while (42)
	{
		if (i == table->nb_philo)
			i = 0;
		pthread_mutex_lock(&table->philo[i].died);
		if (get_time(table) - table->philo[i].last_eat > table->time_die)
		{
			pthread_mutex_unlock(&table->philo[i].died);
			pthread_mutex_lock(&table->print);
			if (table->died == 0)
				printf("[%ld] %d died\n", get_time(table) - table->start_time, table->philo->id);
			table->died = 1;
			pthread_mutex_unlock(&table->print);
			exit(EXIT_FAILURE);
		}
			pthread_mutex_unlock(&table->philo[i].died);
		i++;
	}	
}
void*	simulation(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->id % 2 == 0)
			even_take_fork(philo);
		else if (philo->id %2 == 1)
			odd_take_fork(philo);
		if (philo->got_l_fork == 1 && philo->got_r_fork == 1)
			eat(philo);
		think(philo);
	}
	return (NULL);
}