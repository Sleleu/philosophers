/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/26 00:54:44 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_dead(t_philo *philo)
{
	if (philo->alive == 0)
	{
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d died\n", philo->table->current_time, philo->id);
		return(1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	
	if (philo->got_fork == 2)
	{
		printf("[%ld] %d is eating\n", philo->table->current_time, philo->id);
		usleep(philo->table->time_eat);
		philo->table->current_time = get_time(philo->table);
		philo->got_fork = 0;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	usleep(10);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->got_fork++;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, (philo->id + 1) % (philo->table->nb_philo));	
		pthread_mutex_lock(philo->l_fork);
		philo->got_fork++;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		philo->got_fork++;
		philo->table->current_time = get_time(philo->table);
		printf("[%ld] %d has taken fork %d\n", philo->table->current_time, philo->id, philo->id);	
		pthread_mutex_lock(philo->r_fork);
		philo->got_fork++;
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
	}
	return (NULL);
}