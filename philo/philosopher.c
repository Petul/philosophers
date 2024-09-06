/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/06 14:44:45 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philosophers.h"

static int	start_sleeping(t_philosopher_memory *m)
{
	m->state = SLEEPING;
	m->state_start_time = get_milliseconds();
	if (m->state_start_time < 0)
		return (-1);
	printf("%04zu %d is sleeping\n", m->state_start_time - m->sim_start_time, m->id);
	return (0);
}

static int	start_thinking(t_philosopher_memory *m)
{
	m->state = THINKING;
	m->state_start_time = get_milliseconds();
	if (m->state_start_time < 0)
		return (-1);
	printf("%04zu %d is thinking\n", m->state_start_time - m->sim_start_time, m->id);
	return (0);
}

static int	start_eating(t_philosopher_memory *m)
{
	m->state = EATING;
	m->state_start_time = get_milliseconds();
	if (m->state_start_time < 0)
		return (-1);
	printf("%04zu %d is eating\n", m->state_start_time - m->sim_start_time, m->id);
	return (0);
}

static int	get_forks(t_philosopher_memory *m)
{
	size_t	t;

	if (pthread_mutex_lock(m->fork1) < 0)
		return (-1);
	t = get_milliseconds();
	if (!t)
		return (-1);
	printf("%04zu %d has taken a fork\n", t - m->sim_start_time, m->id);
	if (pthread_mutex_lock(m->fork2) < 0)
		return (-1);
	t = get_milliseconds();
	if (!t)
		return (-1);
	printf("%04zu %d has taken a fork\n", t - m->sim_start_time, m->id);
	return (0);
}

static int	return_forks(t_philosopher_memory *m)
{
	if (pthread_mutex_unlock(m->fork1) < 0)
		return (-1);
	if (pthread_mutex_unlock(m->fork2) < 0)
		return (-1);
	return (0);
}

void	*philosopher(void *philosopher)
{
	t_philosopher_memory	*m;
	size_t					time_now;

	m = (t_philosopher_memory *)philosopher;
	if (m->state == THINKING)
		start_thinking(m);
	else if (m->state == EATING)
	{
		get_forks(m);
		start_eating(m);
	}
	while (1)
	{
		time_now = get_milliseconds();
		if (!time_now)
			return (NULL);
		if (m->state == SLEEPING)
		{
			if (time_now - m->state_start_time >= m->settings->t_sleep)
				start_thinking(m);
		}
		else if (m->state == THINKING)
		{
			get_forks(m);
			start_eating(m);
		}
		else if (m->state == EATING)
		{
			if (time_now - m->state_start_time >= m->settings->t_eat)
			{
				return_forks(m);
				start_sleeping(m);
			}
		}
	}
	pthread_exit(0);
}
