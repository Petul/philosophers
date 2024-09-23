/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:26:45 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "philosophers.h"

static int	launch_philos(t_own_knowledge *ok, t_table *t, pid_t *children)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		ok->id = i;
		children[i] = fork();
		if (children[i] < 0)
			return (-1);
		if (children[i] == 0)
		{
			free(children);
			if (init_philo_semaphores(ok) < 0)
				return (-1);
			philo(ok);
		}
		i++;
	}
	return (0);
}

static int	cleanup_children(pid_t *children)
{
	kill_philos(children);
	free(children);
	return (-1);
}

int	run_simulation(t_table *t)
{
	t_own_knowledge	ok;
	pid_t			*children;
	pid_t			pid_meal_monitor;

	children = malloc(sizeof(pid_t) * (t->n_philos + 1));
	if (!children)
		return (-1);
	ft_memset(children, 0, sizeof(pid_t) * (t->n_philos + 1));
	t->t_sim_start = get_milliseconds() + (2 * t->n_philos);
	init_philo(&ok, t);
	if (launch_philos(&ok, t, children) < 0)
		return (cleanup_children(children));
	pid_meal_monitor = fork();
	if (pid_meal_monitor < 0)
		return (cleanup_children(children));
	if (pid_meal_monitor == 0)
	{
		free(children);
		meal_monitor(t);
	}
	sem_wait(t->sem_death);
	kill_philos(children);
	kill(pid_meal_monitor, SIGKILL);
	free(children);
	return (0);
}
