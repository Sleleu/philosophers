/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 23:16:02 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	time_to_eat(t_philo *philo)
{
	printf("Test philo %d\n", philo->id + 1);
}

void*	simulation(void *arg)
{
	t_philo *philo;
		
	philo = (t_philo *)arg;
	//while (ft_is_dead(philo))
//	{
		time_to_eat(philo);
//	}
	return (NULL);
}