/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:12:41 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "philosophers.h"

static void	init_philo(t_own_knowledge *ok, t_table *t)
{
	ok->id = 0;
	ok->cs = THINKING;
	ok->table = t;
	ok->n_meals = 0;
	ok->sem_death = t->sem_death;
	ok->t_last_meal = t->t_sim_start;
}

static void	kill_philos(pid_t *children, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		kill(children[i], 1);
		i++;
	}
}

int	run_simulation(t_table *t)
{
	int				i;
	size_t			sim_start;
	t_own_knowledge	ok;
	pid_t			*children;

	children = malloc(sizeof(pid_t) * t->n_philos);
	if (!children)
		return (-1);
	t->t_sim_start = get_milliseconds() + START_DELAY;
	init_philo(&ok, t);
	i = 0;
	while (i < t->n_philos)
	{
		ok.id = i;
		children[i] = fork();
		if (children[i] < 0)
			return (-1); // Handle error
		if (children[i] == 0)
			philo(&ok);
		i++;
	}
	sem_wait(t->sem_death);
	kill_philos(children, t->n_philos);
	return (0);
}
