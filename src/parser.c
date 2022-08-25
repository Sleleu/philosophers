/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:29:27 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/25 22:11:36 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	ft_check_arg(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		ft_error();
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				ft_error();
			j++;
		}
		if (ft_atoi(argv[i]) == 0)
			ft_error();
		i++;
	}
}

t_philo	*ft_alloc_array(t_table *table)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philo)
		return (0);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork)
		{
			free(philo);
			return (NULL);
		}
	return (philo);
}

void	ft_get_data(t_table *table, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < table->nb_philo)
	{
		philo[i].id = i;
		philo[i].right_fork = 0;
		philo[i].left_fork = 0;
		philo[i].table = table;
		i++;
	}
}

void	ft_parsing(int argc, char **argv, t_table *table)
{
	t_philo *philo;
	
	ft_check_arg(argv, argc);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]) * 1000;
	table->time_eat = ft_atoi(argv[3]) * 1000;
	table->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		table->nb_eat = ft_atoi(argv[5]);	
	philo = ft_alloc_array(table);
	ft_get_data(table, philo);
	ft_start_philo(table, philo);
}