/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 14:12:05 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	ft_print(philo, THINK);
	usleep(400);
}

void	get_some_sleep_bro(t_philo *philo)
{
	ft_print(philo, SLEEP);
	usleep(philo->table->time_sleep * 1000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, FORK);
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK);
	ft_print(philo, EAT);
	usleep(philo->table->time_eat * 1000);
	pthread_mutex_lock(&philo->table->eat_check);
	if (philo->nb_eat != 0)
		philo->last_eat = get_time();
	if (philo->nb_eat != -1 && philo->nb_eat != 0)
		philo->nb_eat--;
	pthread_mutex_unlock(&philo->table->eat_check);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	get_some_sleep_bro(philo);
}

void	*controller(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	while (42)
	{
		if (i == table->nb_philo)
			i = 0;
		usleep(1000);
		pthread_mutex_lock(&table->eat_check);
		if (get_time() - table->philo[i].last_eat > table->time_die)
		{
			pthread_mutex_unlock(&table->eat_check);
			pthread_mutex_lock(&table->print);
			if (table->died == 0)
				printf("[%ld] %d died\n", get_time()
					- table->start_time, table->philo[i].id + 1);
			table->died = 1;
			pthread_mutex_unlock(&table->print);
			return (NULL);
		}
		pthread_mutex_unlock(&table->eat_check);
		i++;
	}	
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(8000);
	pthread_mutex_lock(&philo->table->eat_check);
	while (philo->table->died == 0)
	{
		pthread_mutex_unlock(&philo->table->eat_check);
		eat(philo);
		if (philo->table->nb_philo == 1)
			return (NULL);
		think(philo);
		pthread_mutex_lock(&philo->table->eat_check);
	}
	pthread_mutex_unlock(&philo->table->eat_check);
	return (NULL);
}
