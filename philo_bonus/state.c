/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:00:36 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 11:14:30 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_state	get_state(t_own_knowledge *ok)
{
	t_state	state;

	pthread_mutex_lock(&ok->mtx_state);
	state = ok->cs;
	pthread_mutex_unlock(&ok->mtx_state);
	return (state);
}

int	set_state(t_own_knowledge *ok, t_state state)
{
	pthread_mutex_lock(&ok->mtx_state);
	ok->cs = state;
	if (state == EATING)
	{
		if (print_eat(ok) < 0)
			return (-1);
	}
	else if (state == THINKING)
	{
		if (philo_print(ok, "%04zu %d is thinking\n", ok->id) < 0)
			return (-1);
	}
	else if (state == SLEEPING)
	{
		if (philo_print(ok, "%04zu %d is sleeping\n", ok->id) < 0)
			return (-1);
	}
	pthread_mutex_unlock(&ok->mtx_state);
	return (0);
}
