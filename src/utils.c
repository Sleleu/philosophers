/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:58:52 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 14:03:23 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_print(t_philo *philo, int print)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->died == 0)
	{
		if (print == 1)
			printf("[%ld] %d has taken a fork\n", get_time()
				- philo->table->start_time, philo->id + 1);
		else if (print == 2 && philo->nb_eat != 0)
			printf("[%ld] %d is eating\n", get_time()
				- philo->table->start_time, philo->id + 1);
		else if (print == 3)
			printf("[%ld] %d is sleeping\n", get_time()
				- philo->table->start_time, philo->id + 1);
		else if (print == 4)
			printf("[%ld] %d is thinking\n", get_time()
				- philo->table->start_time, philo->id + 1);
	}	
	pthread_mutex_unlock(&philo->table->print);
}

long int	ft_atoi(const char *str)
{
	long int		result;
	long int		sign;

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
