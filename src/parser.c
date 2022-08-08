/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:22:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/08 18:57:06 by sleleu           ###   ########.fr       */
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

void	ft_set_table(t_table *table)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i++ < table->nb_philo)
	{
		pthread_create(&table->philo[i], NULL, &routine, NULL);
		pthread_mutex_init(&table->fork[i], NULL);
	}
	while (j++ < table->nb_philo)
	{
		pthread_join(table->philo[j], NULL);
	}
}

int	ft_parsing(int argc, char **argv, t_table *table)
{
	ft_check_arg(argv, argc);
	table->nb_philo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->t_must_eat = ft_atoi(argv[5]);
	table->philo = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo)
		return (0);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork)
		return (0);
	ft_set_table(table);
	return (1);
}