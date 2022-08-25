/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:52:01 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 20:09:03 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void*	simulation(void *arg)
{
	t_philo *philo;
	int i = 5;
	
	philo = (t_philo *)arg;
	while (i > 0)
	{
		printf("Test philo %d\n", philo->id);
		i--;
	}
	return (NULL);
}