/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/27 03:17:52 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_dead(t_philo *philo)
{
	if (philo->alive == 0)
	{
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d died\n", philo->table->current_time, philo->id);
		return (1);
	}
	return (0);
}

void	think(t_philo *philo)
{
	philo->table->current_time = get_time(philo->table);
	printf("[%ld] %d is thinking\n", philo->table->current_time, philo->id);
	usleep(philo->table->time_sleep);
	philo->table->current_time = get_time(philo->table);
	printf("[%ld] %d stop thinking\n", philo->table->current_time, philo->id);
}

void	get_some_sleep(t_philo *philo)
{
	philo->table->current_time = get_time(philo->table);
	printf("[%ld] %d is sleeping\n", philo->table->current_time, philo->id);
	usleep(philo->table->time_sleep);
	philo->table->current_time = get_time(philo->table);
	printf("[%ld] %d is waking up\n", philo->table->current_time, philo->id);
}

void	eat(t_philo *philo)
{
	/*if (philo->got_r_fork == 0 || philo->got_l_fork == 0)
	{
		if (philo->got_l_fork == 1)
			pthread_mutex_unlock(philo->l_fork);
		if (philo->got_r_fork == 1)
			pthread_mutex_unlock(philo->r_fork);
		philo->got_l_fork = 0;
		//usleep(500);
	}*/
	if (philo->got_r_fork && philo->got_l_fork)
	{
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d is eating\n", philo->table->current_time, philo->id);
		usleep(philo->table->time_eat);
		philo->table->current_time = get_time(philo->table);
		philo->got_l_fork = 0;
		philo->got_r_fork = 0;
		pthread_mutex_unlock(philo->l_fork);
		printf("[%ld] %d free fork %d\n", philo->table->current_time, philo->id, philo->id);	
		pthread_mutex_unlock(philo->r_fork);
		printf("[%ld] %d free fork %d\n", philo->table->current_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));	
		get_some_sleep(philo);
	}
	usleep(100);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->got_r_fork = 1;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));	
		pthread_mutex_lock(philo->l_fork);
		philo->got_l_fork = 1;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, philo->id);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->got_l_fork = 1;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, philo->id);	
		pthread_mutex_lock(philo->r_fork);
		philo->got_r_fork = 1;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));
	}
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
			table->current_time = get_time(table);
			printf("[%ld] %d died\n", table->current_time, table->philo[i].id);
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
		take_fork(philo);
		eat(philo);
		think(philo);
		if (philo->id == 3)
			philo->alive = 0; // TEST FONCTION CONTROLLER;
	}
	return (NULL);
}