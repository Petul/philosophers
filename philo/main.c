/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/09 13:09:49 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	s->n_philos = ft_atoi(argv[1]);
	if (s->n_philos < 1)
		return (-1);
	s->t_die = (size_t)ft_atoi(argv[2]);
	s->t_eat = (size_t)ft_atoi(argv[3]);
	s->t_sleep = (size_t)ft_atoi(argv[4]);
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


// static	int	watch_philosophers(t_philosopher_memory *m, int n_philos)
// {
// 	int	i;
//
// 	i = 0;
//
// }

t_table	*prepare_table(t_settings *s, pthread_mutex_t *mtx_forks, pthread_t *th_philos)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->n_philos = s->n_philos;
	table->th_philos = th_philos;
	table->mtx_forks = mtx_forks;
	return (table);
}

static t_own_knowledge	*prepare_philos(t_settings *s, t_shared_knowledge *sk, t_table *table)
{
	t_own_knowledge	*ok;
	int	i;

	ok = calloc(s->n_philos, sizeof(t_own_knowledge));
	if (!ok)
		return (NULL);
	i = 0;
	while (i < s->n_philos)
	{
		ok[i].id = i;
		ok[i].cs = THINK;
		ok[i].mtx_fork1 = &table->mtx_forks[i];
		if (i + 1 >= s->n_philos)
			ok[i].mtx_fork2 = &table->mtx_forks[0];
		else
			ok[i].mtx_fork2 = &table->mtx_forks[i + 1];
		ok[i].sk = sk;
		pthread_mutex_init(&ok[i].mtx_last_meal, NULL); // Handle failure
		i++;
	}
	return (ok);
}


static int	philosophers(t_settings *s, pthread_mutex_t *mtx_forks, pthread_t *th_philos)
{
	t_table				*table;
	t_own_knowledge		*ok;
	t_shared_knowledge	*sk;

	table = prepare_table(s, mtx_forks, th_philos);
	if (!table)
		return (-1);
	sk = create_shared_knowledge(s);
	if (!sk)
	{
		free(table);
		return (1);
	}
	ok = prepare_philos(s, sk, table);
	if (!ok)
	{
		destroy_shared_knowledge(sk);
		free(table);
		return (1);
	}
	return (run_simulation(table, ok));
}

int	main(int argc, char **argv)
{
	pthread_t		*th_philos;
	pthread_mutex_t	*mtx_forks;
	t_settings		s;
	int				retval;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number or arguments\n");
		return(1);
	}
	if (parse_args(argc, argv, &s) < 0)
		printf("Error: incorrect argument(s)\n");
	mtx_forks = create_forks(s.n_philos);
	if (!mtx_forks)
		return (1);
	th_philos = malloc(sizeof(pthread_t) * s.n_philos);
	if (!th_philos)
	{
		free(mtx_forks);
		return (1);
	}
	retval = 0;
	if (philosophers(&s, mtx_forks, th_philos) < 0)
		retval = 1;
	destroy_forks(mtx_forks, s.n_philos);
	free(th_philos);
	return (retval);
}


