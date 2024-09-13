/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 14:43:01 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static int	stop_simulation(t_own_knowledge *ok)
{
	if (pthread_mutex_lock(&ok->table->sim_running_mtx) != 0)
		return (-1);
	ok->table->sim_running = 0;
	if (pthread_mutex_unlock(&ok->table->sim_running_mtx) != 0)
		return (-1);
	return (0);
}

static	int	check_meals(t_own_knowledge *ok, t_table *t, int *n_ate_enough)
{
	int		n_meals;

	n_meals = get_n_meals(ok);
	if (n_meals < 0)
		return (-1);
	if (n_meals >= t->n_eat)
		(*n_ate_enough)++;
	return (0);
}

static	int check_death(t_own_knowledge *ok)
{
	ssize_t	time;
	ssize_t	t_last_meal;

	if (get_state(ok) == EXITED)
	{
		stop_simulation(ok);
		return (0);
	}
	t_last_meal = get_last_meal(ok);
	time = get_milliseconds();
	if (t_last_meal < 0 || time < 0)
		return (-1);
	if	(time > t_last_meal && (size_t)(time - t_last_meal) >= ok->table->t_die)
	{
		if (stop_simulation(ok) < 0)
			return (-1);
		if (print_died(ok, ok->id, (t_last_meal + ok->table->t_die) - ok->table->t_sim_start) < 0)
			return (-1);
		return (0);
	}
	return (1);
}
static	int	watch_philosophers(t_table *t, t_own_knowledge *ok)
{
	int		i;
	int		n_ate_enough;
	int		ret;

	while (1)
	{
		n_ate_enough = 0;
		i = 0;
		while (i < t->n_philos)
		{
			ret = check_death(&ok[i]);
			if (ret != 1)
				return (ret);
			if (t->n_eat >= 0)
				if (check_meals(ok, t, &n_ate_enough) < 0)
					return (-1);
			i++;
		}
		if (n_ate_enough == t->n_philos)
		{
			if (stop_simulation(ok) < 0)
				return (-1);
			return (0);
		}
	}
}

int	run_simulation(t_table *table, t_own_knowledge *ok)
{
	int		i;
	ssize_t	sim_start;

	sim_start = get_milliseconds();
	if (sim_start < 0)
		return (-1);
	ok->table->t_sim_start = sim_start;
	ok->table->t_sim_start += START_DELAY;
	i = 0;
	while (i < table->n_philos)
	{
		ok[i].t_last_meal = ok->table->t_sim_start;
		pthread_create(&table->th_philos[i], NULL, &philosopher, &ok[i]); // Handle failure
		i++;
	}
	i = 0;
	if (watch_philosophers(table, ok) < 0)
		return (-1);
	while (i < table->n_philos)
	{
		pthread_join(table->th_philos[i], NULL); 
		i++;
	}
	return (0);
}
