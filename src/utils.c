/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:58:52 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/30 01:36:25 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_usleep(useconds_t useconds, t_philo *philo)
{	
	if (philo->table->time_die < useconds)
	{
		useconds = philo->table->time_die;
		usleep(useconds * 1000);
		pthread_mutex_lock(&philo->died);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->died);
		ft_is_dead(philo);
		return (0);
	}
	usleep(useconds * 1000);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}