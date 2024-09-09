/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/09 12:57:52 by pleander         ###   ########.fr       */
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
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	printf("%04zu %d is sleeping\n", ok->t_cs_start - ok->sk->t_sim_start, ok->id);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}

static int	start_thinking(t_own_knowledge *ok)
{
	ok->cs = THINK;
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	printf("%04zu %d is thinking\n", ok->t_cs_start - ok->sk->t_sim_start, ok->id);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}

static int	start_eating(t_own_knowledge *ok)
{
	ok->cs = EAT;
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	printf("%04zu %d is eating\n", ok->t_cs_start - ok->sk->t_sim_start, ok->id);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}

static int	get_forks(t_own_knowledge *ok)
{
	size_t	t;

	if (pthread_mutex_lock(ok->mtx_fork1) < 0)
		return (-1);
	t = get_milliseconds();
	if (!t)
		return (-1);
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	printf("%04zu %d has taken a fork\n", t - ok->sk->t_sim_start, ok->id);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	if (pthread_mutex_lock(ok->mtx_fork2) < 0)
		return (-1);
	t = get_milliseconds();
	if (!t)
		return (-1);
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	printf("%04zu %d has taken a fork\n", t - ok->sk->t_sim_start, ok->id);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
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

void	*philosopher(void *own_knowledge)
{
	t_own_knowledge			*ok;
	size_t					time_now;

	ok = (t_own_knowledge *)own_knowledge;
	if (delay_start(ok) < 0)
		return (NULL);
	start_thinking(ok);
	while (1)
	{
		time_now = get_milliseconds();
		if (time_now < 0)
			return (NULL);
		if (ok->cs == SLEEP)
		{
			if (time_now - ok->t_cs_start >= ok->sk->t_sleep)
				start_thinking(ok);
		}
		else if (ok->cs == THINK)
		{
			get_forks(ok);
			start_eating(ok);
		}
		else if (ok->cs == EAT)
		{
			if (time_now - ok->t_cs_start >= ok->sk->t_eat)
			{
				return_forks(ok);
				start_sleeping(ok);
			}
		}
	}
	pthread_exit(0);
}
