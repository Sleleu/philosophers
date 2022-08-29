/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/29 19:49:34 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_dead(t_philo *philo)
{
	if (philo->alive == 0)
	{
		printf("[%ld] %d died\n", get_time(philo->table) - philo->table->start_time, philo->id);
		return (1);
	}
	return (0);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("[%ld] %d is thinking\n", get_time(philo->table) - philo->table->start_time, philo->id);
	usleep(philo->table->time_sleep);
	pthread_mutex_unlock(&philo->table->print);
}

void	get_some_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("[%ld] %d is sleeping\n", get_time(philo->table) - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->time_sleep);
}

/*
void	eat(t_philo *philo)
{
	if (philo->got_r_fork == 0 || philo->got_l_fork == 0)
	{
		if (philo->got_l_fork == 1)
			pthread_mutex_unlock(philo->l_fork);
		if (philo->got_r_fork == 1)
			pthread_mutex_unlock(philo->r_fork);
		philo->got_l_fork = 0;
		philo->got_r_fork = 0;
	}
	if (philo->got_r_fork && philo->got_l_fork)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("[%ld] %d is eating\n", get_time(philo->table) - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->time_eat);
		philo->got_l_fork = 0;
		philo->got_r_fork = 0;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		get_some_sleep(philo);
	}
	usleep(100);
}*/

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo->got_r_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(philo->l_fork);
	philo->got_l_fork = 1;
	pthread_mutex_lock(&philo->table->print);
	printf("[%ld] %d has taken fork %d\n", get_time(philo->table) - philo->table->start_time, philo->id, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(&philo->table->print);
	printf("[%ld] %d is eating\n", get_time(philo->table) - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->time_eat);
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
		if (table->philo[i].alive == 0)
		{
			pthread_mutex_lock(&table->philo[i].died);
			printf("[%ld] %d died\n", get_time(table) - table->start_time, table->philo[i].id);
			exit(EXIT_FAILURE);
			pthread_mutex_unlock(&table->philo[i].died);
		}
		i++;
	}	
}
void*	simulation(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (42)
	{
		eat(philo);
		think(philo);
	}
	return (NULL);
}