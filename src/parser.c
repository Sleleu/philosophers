/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:29:27 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/31 14:03:58 by sleleu           ###   ########.fr       */
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
	int			i;
	long int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		ft_error();
	while (argv[i])
	{
		j = ft_atoi(argv[i]);
		if (j > 2147483647)
			ft_error();
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				ft_error();
			j++;
		}
		if (ft_atoi(argv[1]) == 0)
			ft_error();
		i++;
	}
}

t_philo	*ft_alloc_array(t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philo)
		return (NULL);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	ft_get_data(int argc, char **argv, t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		philo[i].id = i;
		philo[i].l_fork = &table->fork[i];
		philo[i].r_fork = &table->fork[(i + 1) % (table->nb_philo)];
		philo[i].alive = 1;
		philo[i].last_eat = get_time();
		philo[i].table = table;
		if (argc == 6)
		{
			if (ft_atoi(argv[5]) < 0)
				ft_error();
			else
			philo[i].nb_eat = ft_atoi(argv[5]);
		}
		else
			philo[i].nb_eat = -1;
		i++;
	}
}

void	ft_parsing(int argc, char **argv, t_table *table)
{
	t_philo	*philo;

	ft_check_arg(argv, argc);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->died = 0;
	philo = ft_alloc_array(table);
	ft_get_data(argc, argv, table, philo);
	table->philo = philo;
	ft_start_philo(table, philo);
}
