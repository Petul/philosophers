/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:33:57 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:04:10 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "philosophers.h"

int	prepare_table(t_table *table, t_settings *s)
{
	table->n_philos = s->n_philos;
	table->n_eat = s->n_eat;
	table->t_sleep = s->t_sleep;
	table->t_die = s->t_die;
	table->t_eat = s->t_eat;
	table->t_sim_start = 0;
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, s->n_philos);
	if (table->sem_forks < 0)
		return (-1);
	table->sem_death = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	if (table->sem_death < 0)
		return (-1);
	table->sem_eaten_enough = NULL; //TODO
	return (0);
}
