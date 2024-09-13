/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 10:20:39 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static int	stop_simulation(t_own_knowledge *ok)
{
	if (pthread_mutex_lock(&ok->sk->sim_running_mtx) != 0)
		return (-1);
	ok->sk->sim_running = 0;
	if (pthread_mutex_unlock(&ok->sk->sim_running_mtx) != 0)
		return (-1);
	return (0);
}

static int	watch_philosophers(t_table *t, t_own_knowledge *ok)
{
	int		i;
	ssize_t	time;
	ssize_t	t_last_meal;
	int		all_eaten;
	int		n_meals;

	if (delay_start(ok) < 0)
		return (-1);
	while (1)
	{
		all_eaten = 1;
		i = 0;
		while (i < t->n_philos)
		{
			if (get_state(&ok[i]) == EXITED)
			{
				stop_simulation(&ok[i]);
				return (0);
			}
			t_last_meal = get_last_meal(&ok[i]);
			if (t_last_meal < 0)
				return (-1);
			time = get_milliseconds();
			if (time < 0)
				return (-1);
			if	(time > t_last_meal && (size_t)(time - t_last_meal) >= ok->sk->t_die)
			{
				if (stop_simulation(&ok[i]) < 0)
					return (-1);
				if (print_died(ok, i, (t_last_meal + ok->sk->t_die) - ok->sk->t_sim_start) < 0)
					return (-1);
				return (0);
			}
			if (t->n_eat >= 0)
			{
				n_meals = get_n_meals(ok);
				if (n_meals < 0)
					return (-1);
				if (n_meals < t->n_eat)
					all_eaten = 0;
			}
			i++;
		}
		if (t->n_eat >= 0 && all_eaten)
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
	ok->sk->t_sim_start = sim_start;
	ok->sk->t_sim_start += START_DELAY;
	i = 0;
	while (i < table->n_philos)
	{
		ok[i].t_last_meal = ok->sk->t_sim_start;
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
