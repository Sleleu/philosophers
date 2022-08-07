/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:22:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/07 18:41:16 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_parsing(char **argv, t_table *table)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	table->nb_philo = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo)
		return (0);
	while (i++ < table->nb_philo)
		pthread_create(&table->philo[i], NULL, &routine, NULL);
	while (j++ < table->nb_philo)
		pthread_join(table->philo[j], NULL);
	return (1);
}