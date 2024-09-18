/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:03:29 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	if (argc < 5 || argc > 6)
		return (-1);
	s->n_philos = ft_atoi(argv[1]);
	if (s->n_philos < 1)
		return (-1);
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (-1);
	if (!is_number(argv[2]) || !is_number(argv[3]) || !is_number(argv[4]))
		return (-1);
	s->t_die = (size_t)ft_atoi(argv[2]);
	s->t_eat = (size_t)ft_atoi(argv[3]);
	s->t_sleep = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!is_number(argv[5]))
			return (-1);
		s->n_eat = ft_atoi(argv[5]);
		if (s->n_eat < 0)
			return (-1);
	}
	else
		s->n_eat = -1;
	return (0);
}

static int	philosophers(t_settings *s, pthread_t *th_philos)
{
	t_table				table;
	t_own_knowledge		*ok;
	int					retval;

	if (prepare_table(&table, s) < 0)
		return (1);
	retval = run_simulation(&table);
	free(ok);
	return (retval);
}

int	main(int argc, char **argv)
{
	pthread_t		*th_philos;
	t_settings		s;
	int				retval;

	if (parse_args(argc, argv, &s) < 0)
	{
		printf("Error: incorrect argument(s)\n");
		return (1);
	}
	th_philos = malloc(sizeof(pthread_t) * s.n_philos);
	if (!th_philos)
		return (1);
	retval = philosophers(&s, th_philos);
	free(th_philos);
	return (retval);
}
