/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/20 12:27:26 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static void	check_death(t_own_knowledge *ok)
{
	size_t	t;

	delay_start(ok);
	while (1)
	{
		sem_wait(ok->sem_last_meal);
		t = get_milliseconds();
		if (t - ok->t_last_meal >= ok->table->t_die)
		{
			sem_wait(ok->table->sem_print);
			printf("%04zu %d died\n", t - ok->t_last_meal, ok->id);
			sem_post(ok->table->sem_death);
		}
		sem_post(ok->sem_last_meal);
		usleep(500);
	}
}

void	philo(t_own_knowledge *ok)
{
	pthread_t	t;

	pthread_create(&t, NULL, (void *)(void *)check_death, (void *)ok);
	pthread_detach(t);
	delay_start(ok);
	while (1)
	{
		think(ok);
		usleep(500);
		eat(ok);
		rest(ok);
	}
}
