/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:33:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/08 20:54:00 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void*	routine()
{
	int i = 0;
	
	printf("Test from philo %d\n", (int)getpid());
	sleep(2);
	printf("Ending threads\n");
	i++;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table table;
	
	ft_parsing(argc, argv, &table);
	free(table.philo);
	(void)argc;
	return (0);
}