/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:33:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/08/07 18:56:43 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void*	routine()
{
	int i = 0;
	
	printf("Test from philo %d\n", i);
	sleep(2);
	printf("Ending threads\n");
	i++;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table table;
	
	ft_parsing(argv, &table);
	(void)argc;
	return (0);
}