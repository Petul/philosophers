/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/19 15:49:18 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philosophers.h"

static void	think(t_own_knowledge *ok)
{
	pprint(ok, "%04zu %d is thinking\n");
}

static void	eat(t_own_knowledge *ok)
{
	sem_wait(ok->table->sem_grab_forks);
	sem_wait(ok->table->sem_forks);
	pprint(ok, "%04zu %d has taken a fork\n");
	sem_wait(ok->table->sem_forks);
	pprint(ok, "%04zu %d has taken a fork\n");
	sem_wait(ok->sem_last_meal);
	ok->t_last_meal = pprint(ok, "%04zu %d is eating\n");
	sem_post(ok->sem_last_meal);
	sem_post(ok->table->sem_grab_forks);
	sleep_until(ok->t_last_meal + ok->table->t_eat);
	sem_post(ok->table->sem_forks);
	sem_post(ok->table->sem_forks);
}

static void	rest(t_own_knowledge *ok)
{
	size_t	t;
	t = pprint(ok, "%04zu %d is sleeping\n");
	sleep_until(t + ok->table->t_sleep);
}

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
