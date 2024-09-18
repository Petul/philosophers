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
#include <stdlib.h>
#include "philosophers.h"

int	prepare_table(t_table *table, t_settings *s, pthread_mutex_t *mtx_forks,
					pthread_t *th_philos)
{
	table->n_philos = s->n_philos;
	table->th_philos = th_philos;
	table->mtx_forks = mtx_forks;
	table->n_eat = s->n_eat;
	table->t_sleep = s->t_sleep;
	table->t_die = s->t_die;
	table->t_eat = s->t_eat;
	table->sim_running = 1;
	if (pthread_mutex_init(&table->sim_running_mtx, NULL) < 0)
		return (-1);
	if (pthread_mutex_init(&table->print_mtx, NULL) < 0)
		return (-1);
	if (pthread_mutex_init(&table->take_forks_mtx, NULL) < 0)
		return (-1);
	return (0);
}
