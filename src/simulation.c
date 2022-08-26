/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/26 03:02:14 by sleleu           ###   ########.fr       */
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

void*	simulation(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;
	while (42)
	{
		take_fork(philo);
		eat(philo);
		think(philo);
	}
	return (NULL);
}