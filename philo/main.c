/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/04 14:57:24 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	s->n_philos = ft_atoi(argv[1]);
	if (s->n_philos < 1)
		return (-1);
	s->t_die = ft_atoi(argv[2]);
	s->t_eat = ft_atoi(argv[3]);
	s->t_sleep = ft_atoi(argv[4]);
	if (s->t_die < 0 || s->t_eat < 0 || s->t_sleep < 0)
		return (-1);
	if (argc == 6)
	{
		s->n_eat = ft_atoi(argv[5]);
		if (s->n_eat < 0)
			return (-1);
	}
	else
		s->n_eat = -1;
	return (0);
}


int	main(int argc, char **argv)
{
	t_settings	s;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number or arguments\n");
		return(1);
	}
	if (parse_args(argc, argv, &s) < 0)
		printf("Error: incorrect argument(s)\n");
}
