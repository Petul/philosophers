/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/10 10:00:32 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philosophers.h"

static int	start_sleeping(t_own_knowledge *ok)
{
	ok->cs = SLEEP;
	if (philo_print(ok, "%04zu %d is sleeping\n", ok->id) < 0)
		return (-1);
	return (0);
}

static int	start_thinking(t_own_knowledge *ok)
{
	ok->cs = THINK;
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (philo_print(ok, "%04zu %d is thinking\n", ok->id) < 0)
		return (-1);
	return (0);
}

static int	start_eating(t_own_knowledge *ok)
{
	ok->cs = EAT;
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (philo_print(ok, "%04zu %d is eating\n", ok->id) < 0)
		return (-1);
	return (0);
}

static int	get_forks(t_own_knowledge *ok)
{
	size_t	t;

	if (pthread_mutex_lock(ok->mtx_fork1) < 0)
		return (-1);
	if (philo_print(ok, "%04zu %d has taken a fork\n",  ok->id) < 0)
		return (-1);
	if (pthread_mutex_lock(ok->mtx_fork2) < 0)
		return (-1);
	if (philo_print(ok, "%04zu %d has taken a fork\n",  ok->id) < 0)
		return (-1);
	return (0);
}

static int	return_forks(t_own_knowledge *ok)
{
	if (pthread_mutex_unlock(ok->mtx_fork1) < 0)
		return (-1);
	if (pthread_mutex_unlock(ok->mtx_fork2) < 0)
		return (-1);
	return (0);
}

static int	delay_start(t_own_knowledge *ok)
{
	ssize_t	t;

	t = get_milliseconds();
	if (t < 0)
		return (-1);
	while ((size_t)t < ok->sk->t_sim_start)
	{
		t = get_milliseconds();
		if (t < 0)
			return (-1);
	}
	return (1);
}

static void *error_exit(void)
{
	printf("Error\n");
	return (NULL);
}

void	*philosopher(void *own_knowledge)
{
	t_own_knowledge			*ok;
	size_t					time_now;

	ok = (t_own_knowledge *)own_knowledge;
	if (delay_start(ok) < 0)
		return (NULL);
	if (start_thinking(ok) < 0)
		return (error_exit());
	while (1)
	{
		time_now = get_milliseconds();
		if (time_now < 0)
			return (NULL);
		if (ok->cs == SLEEP)
		{
			if (time_now - ok->t_cs_start >= ok->sk->t_sleep)
				if (start_thinking(ok) < 0)
					return (error_exit());
		}
		else if (ok->cs == THINK)
		{
			if (get_forks(ok) < 0)
				return (error_exit());
			if (start_eating(ok) < 0)
				return (error_exit());
		}
		else if (ok->cs == EAT)
		{
			if (time_now - ok->t_cs_start >= ok->sk->t_eat)
			{
				if (return_forks(ok) < 0)
					return (error_exit());
				if (start_sleeping(ok) < 0)
					return (error_exit());
			}
		}
		usleep(500);
	}
	pthread_exit(0);
}
