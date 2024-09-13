/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 14:44:40 by pleander         ###   ########.fr       */
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
int	wait_or_exit(t_table *table, size_t	msec)
{
	ssize_t	t0;
	ssize_t	t;
	int		res;

	t0 = get_milliseconds();
	if (t0 < 0)
		return (-1);
	t = t0;
	while ((size_t)(t - t0) < msec)
	{
		usleep(500);
		res = is_sim_running(table);
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

int	is_sim_running(t_table *table)
{
	if (pthread_mutex_lock(&table->sim_running_mtx) != 0)
		return (-1);
	if (table->sim_running == 0)
	{
		if (pthread_mutex_unlock(&table->sim_running_mtx) != 0)
			return (-1);
		return (0);
	}
	if (pthread_mutex_unlock(&table->sim_running_mtx) != 0)
		return (-1);
	return (1);
}

int	delay_start(t_own_knowledge *ok)
{
	ssize_t	t;

	t = get_milliseconds();
	if (t < 0)
		return (-1);
	while ((size_t)t < ok->table->t_sim_start)
	{
		t = get_milliseconds();
		if (t < 0)
			return (-1);
	}
	return (1);
}

int	is_number(char	*str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
