/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/19 15:28:14 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "philosophers.h"

static void	init_philo(t_own_knowledge *ok, t_table *t)
{
	ok->id = 0;
	ok->table = t;
	ok->n_meals = 0;
	ok->sem_death = t->sem_death;
	ok->t_last_meal = t->t_sim_start;
}

static void	kill_philos(pid_t *children, int n)
{
	int i;

	printf("Killing philos\n");
	i = 0;
	while (i < n)
	{
		kill(children[i], SIGKILL);
		i++;
	}
}

static int	init_philo_semaphores(t_own_knowledge *ok)
{
	char	*sem_name;

	sem_name = make_sem_name("sem_last_meal", ok->id);
	sem_unlink(sem_name);
	ok->sem_last_meal = sem_open(sem_name, O_CREAT, 0644, 1);
	free(sem_name);
	if (ok->sem_last_meal == SEM_FAILED)
		return (-1);
	return (0);
}

int	run_simulation(t_table *t)
{
	int				i;
	t_own_knowledge	ok;
	pid_t			*children;

	children = malloc(sizeof(pid_t) * t->n_philos);
	if (!children)
		return (-1);
	t->t_sim_start = get_milliseconds() + (2 * t->n_philos);
	init_philo(&ok, t);
	i = 0;
	while (i < t->n_philos)
	{
		ok.id = i;
		children[i] = fork();
		if (children[i] < 0)
			return (-1); // Handle error
		if (children[i] == 0)
		{
			init_philo_semaphores(&ok);
			philo(&ok);
		}
		i++;
	}
	sem_wait(t->sem_death);
	kill_philos(children, t->n_philos);
	free(children);
	return (0);
}
