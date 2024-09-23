/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:03:48 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <sys/time.h>

size_t	get_milliseconds(void)
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
	size_t	t0;
	size_t	t;
	int		res;

	t0 = get_milliseconds();
	t = t0;
	while ((t - t0) < msec)
	{
		usleep(500);
		res = is_sim_running(table);
		if (res == 0)
			return (1);
		if (res == -1)
			return (-1);
		t = get_milliseconds();
	}
	return (0);
}

int	is_sim_running(t_table *table)
{
	pthread_mutex_lock(&table->sim_running_mtx);
	if (table->sim_running == 0)
	{
		pthread_mutex_unlock(&table->sim_running_mtx);
		return (0);
	}
	pthread_mutex_unlock(&table->sim_running_mtx);
	return (1);
}

int	delay_start(t_own_knowledge *ok)
{
	size_t	t;

	t = get_milliseconds();
	while (t < ok->table->t_sim_start)
		t = get_milliseconds();
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
