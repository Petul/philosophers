/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/06 11:38:35 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h> //

ssize_t	get_milliseconds(void)
{
	struct timeval	tv;
	size_t			millis;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (millis);
}

/**
 * @brief Waits or exits early if the simulation has ended
 *
 * @param sk 
 * @param usec 
 * @return -1: Error, 0: Wait finished, 1: Simulation has ended
 */
int	wait_or_exit(t_shared_knowledge *sk, size_t	msec)
{
	size_t	t0;
	size_t	t;
	int		res;

	t0 = get_milliseconds();
	if (t0 < 0)
		return (-1);
	t = t0;
	while (t - t0 < msec)
	{
		usleep(500);
		res = is_sim_running(sk);
		if (res == 0)
			return (1);
		if (res == -1)
			return (-1);
		t = get_milliseconds();
		if (t < 0)
			return (-1);
	}
	return (0);
}

int	is_sim_running(t_shared_knowledge *sk)
{
	if (pthread_mutex_lock(&sk->sim_running_mtx) != 0)
		return (-1);
	if (sk->sim_running == 0)
	{
		if (pthread_mutex_unlock(&sk->sim_running_mtx) != 0)
			return (-1);
		return (0);
	}
	if (pthread_mutex_unlock(&sk->sim_running_mtx) != 0)
		return (-1);
	return (1);
}

int	delay_start(t_own_knowledge *ok)
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
