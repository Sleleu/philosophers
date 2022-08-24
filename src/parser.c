/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:22:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/22 16:51:55 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void ft_check_arg(char **argv, int argc)
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

int	ft_get_data(int argc, char **argv, t_table *table)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]) * 1000;
	table->time_eat = ft_atoi(argv[3]) * 1000;
	table->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		table->nb_eat = ft_atoi(argv[5]) * 1000;
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (0);
	table->fork = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->fork)
	{
		// free les structures philosophes si l'alloc rate
		return (0);
	}
	return (1);
}

void	ft_parsing(int argc, char **argv, t_table *table)
{
	ft_check_arg(argv, argc);
	if (ft_get_data(argc, argv, table) == 0)
		ft_error();
}