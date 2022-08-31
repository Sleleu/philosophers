/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 09:23:41 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	ft_print(philo, THINK);
	usleep(400);
}

void	get_some_sleep(t_philo *philo)
{
	ft_print(philo, SLEEP);
	usleep(philo->table->time_sleep * 1000);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK);
}

void	eat(t_philo *philo)
{
	ft_print(philo, EAT);
	usleep(philo->table->time_eat * 1000);
	pthread_mutex_lock(&philo->eat_check);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->eat_check);
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
		usleep(5000);
		pthread_mutex_lock(&table->philo[i].eat_check);
		if (get_time() - table->philo[i].last_eat > table->time_die)
		{
			pthread_mutex_unlock(&table->philo[i].eat_check);
			pthread_mutex_lock(&table->print);
			if (table->died == 0)
				printf("[%ld] %d died\n", get_time() - table->start_time, table->philo[i].id + 1);
			table->died = 1;
			pthread_mutex_unlock(&table->print);
			exit(0);
		}
			pthread_mutex_unlock(&table->philo[i].eat_check);
		i++;
	}	
}
void*	simulation(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(15000);
	while (42)
	{
		take_fork(philo);
		eat(philo);
		think(philo);
	}
	return (NULL);
}