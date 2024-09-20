/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/20 13:47:57 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
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

static void	clear_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_GRAB_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_SIM_ENDED);
	sem_unlink(SEM_EATEN_ENOUGH);
}

static int	philosophers(t_settings *s)
{
	t_table				table;
	int					retval;

	if (prepare_table(&table, s) < 0)
		return (1);
	retval = run_simulation(&table);
	sem_close(table.sem_print);
	sem_close(table.sem_forks);
	sem_close(table.sem_grab_forks);
	sem_close(table.sem_death);
	sem_close(table.sem_eaten_enough);
	return (retval);
}

int	main(int argc, char **argv)
{
	t_settings		s;
	int				retval;

	if (parse_args(argc, argv, &s) < 0)
	{
		printf("Error: incorrect argument(s)\n");
		return (1);
	}
	clear_semaphores();
	retval = philosophers(&s);
	return (retval);
}
