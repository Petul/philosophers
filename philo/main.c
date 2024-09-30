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
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (-1);
	if (!is_number(argv[1]) || !is_number(argv[2]) || !is_number(argv[3]) || !is_number(argv[4]))
		return (-1);
	s->n_philos = ft_atoi(argv[1]);
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

static void	hand_out_utensils(t_own_knowledge *ok, t_table *table, int i)
{
	ok[i].mtx_fork1 = &table->mtx_forks[i];
	if (i == 0)
	{
		ok[i].left_philo = &ok[table->n_philos - 1];
		ok[i].right_philo = &ok[i + 1];
		if (table->n_philos == 1)
			ok[i].mtx_fork2 = ok[i].mtx_fork1;
		else
			ok[i].mtx_fork2 = &table->mtx_forks[i + 1];
	}
	else if (i == table->n_philos - 1)
	{
		ok[i].left_philo = &ok[table->n_philos - 1];
		ok[i].right_philo = &ok[0];
		ok[i].mtx_fork2 = &table->mtx_forks[0];
	}
	else
	{
		ok[i].left_philo = &ok[i - 1];
		ok[i].right_philo = &ok[i + 1];
		ok[i].mtx_fork2 = &table->mtx_forks[i + 1];
	}
}

static t_own_knowledge	*prepare_philos(t_settings *s, t_table *table)
{
	int				i;
	t_own_knowledge	*ok;

	ok = malloc(s->n_philos * sizeof(t_own_knowledge));
	if (!ok)
		return (NULL);
	i = 0;
	while (i < s->n_philos)
	{
		ok[i].id = i;
		ok[i].cs = THINKING;
		ok[i].table = table;
		hand_out_utensils(ok, table, i);
		ok[i].n_meals = 0;
		if (pthread_mutex_init(&ok[i].mtx_last_meal, NULL) < 0)
			return (NULL);
		if (pthread_mutex_init(&ok[i].mtx_state, NULL) < 0)
			return (NULL);
		if (pthread_mutex_init(&ok[i].mtx_n_meals, NULL) < 0)
			return (NULL);
		i++;
	}
	return (ok);
}

static int	philosophers(t_settings *s, pthread_mutex_t *mtx_forks,
						pthread_t *th_philos)
{
	t_table				table;
	t_own_knowledge		*ok;
	int					retval;

	if (prepare_table(&table, s, mtx_forks, th_philos) < 0)
		return (1);
	ok = prepare_philos(s, &table);
	if (!ok)
		return (1);
	retval = run_simulation(&table, ok);
	free(ok);
	return (retval);
}

int	main(int argc, char **argv)
{
	pthread_t		*th_philos;
	pthread_mutex_t	*mtx_forks;
	t_settings		s;
	int				retval;

	if (parse_args(argc, argv, &s) < 0)
	{
		printf("Error: incorrect argument(s)\n");
		return (1);
	}
	mtx_forks = create_forks(s.n_philos);
	if (!mtx_forks)
		return (1);
	th_philos = malloc(sizeof(pthread_t) * s.n_philos);
	if (!th_philos)
	{
		free(mtx_forks);
		return (1);
	}
	retval = philosophers(&s, mtx_forks, th_philos);
	destroy_forks(mtx_forks, s.n_philos);
	free(th_philos);
	return (retval);
}
