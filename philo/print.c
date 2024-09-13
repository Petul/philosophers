/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:24:20 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 09:40:10 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philosophers.h"

int	philo_print(t_own_knowledge *ok, char *fstr, int id)
{
	ssize_t	t;

	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	t = get_milliseconds();
	if (t < 0)
		return (-1);
	if (is_sim_running(ok->sk))
	{
		if (printf(fstr, t - ok->sk->t_sim_start, id) < 0)
			return (-1);
	}
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}

int	print_died(t_own_knowledge *ok, int id, size_t t_death)
{
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	if (printf("%04zu %d died\n", t_death, id) < 0)
		return (-1);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}

int	print_eat(t_own_knowledge *ok)
{
	ssize_t	t_last_meal;

	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	t_last_meal = set_last_meal(ok);
	if (t_last_meal < 0)
	{
		printf("t_last meal smaller than one for %d\n", ok->id);
		return (-1);
	}
	if (is_sim_running(ok->sk))
	{
		if (printf("%04zu %d is eating\n", t_last_meal - ok->sk->t_sim_start, ok->id) < 0)
			return (-1);
	}
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}
