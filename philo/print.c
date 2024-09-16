/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:24:20 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:13:09 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philosophers.h"

int	philo_print(t_own_knowledge *ok, char *fstr, int id)
{
	size_t	t;

	pthread_mutex_lock(&ok->table->print_mtx);
	t = get_milliseconds();
	if (is_sim_running(ok->table))
	{
		if (printf(fstr, t - ok->table->t_sim_start, id) < 0)
			return (-1);
	}
	pthread_mutex_unlock(&ok->table->print_mtx);
	return (0);
}

int	print_died(t_own_knowledge *ok, int id, size_t t_death)
{
	pthread_mutex_lock(&ok->table->print_mtx);
	if (printf("%04zu %d died\n", t_death, id) < 0)
		return (-1);
	pthread_mutex_unlock(&ok->table->print_mtx);
	return (0);
}

int	print_eat(t_own_knowledge *ok)
{
	pthread_mutex_lock(&ok->table->print_mtx);
	set_last_meal(ok);
	if (is_sim_running(ok->table))
	{
		if (printf("%04zu %d is eating\n", get_last_meal(ok)
				- ok->table->t_sim_start, ok->id) < 0)
			return (-1);
	}
	pthread_mutex_unlock(&ok->table->print_mtx);
	return (0);
}
