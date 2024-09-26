/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:22:53 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:27:05 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include "philosophers.h"

void	init_philo(t_own_knowledge *ok, t_table *t)
{
	ok->id = 0;
	ok->table = t;
	ok->n_meals = 0;
	ok->sem_death = t->sem_death;
	ok->t_last_meal = t->t_sim_start;
}

void	kill_philos(pid_t *children)
{
	int	i;

	i = 0;
	while (children[i])
	{
		kill(children[i], SIGKILL);
		i++;
	}
}

int	init_philo_semaphores(t_own_knowledge *ok)
{
	char	*sem_name;

	sem_name = make_sem_name("/sem_last_meal", ok->id);
	sem_unlink(sem_name);
	ok->sem_last_meal = sem_open(sem_name, O_CREAT, 0644, 1);
	free(sem_name);
	if (ok->sem_last_meal == SEM_FAILED)
		return (-1);
	return (0);
}

void	meal_monitor(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		sem_wait(t->sem_eaten_enough);
		i++;
	}
	sem_post(t->sem_death);
	exit(0);
}
