/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:45:23 by pleander          #+#    #+#             */
/*   Updated: 2024/09/20 08:50:12 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_own_knowledge *ok)
{
	pprint(ok, "%04zu %d is thinking\n");
}

static void	grab_forks(t_own_knowledge *ok)
{
	sem_wait(ok->table->sem_grab_forks);
	sem_wait(ok->table->sem_forks);
	pprint(ok, "%04zu %d has taken a fork\n");
	sem_wait(ok->table->sem_forks);
	pprint(ok, "%04zu %d has taken a fork\n");
	sem_post(ok->table->sem_grab_forks);
}

static void	return_forks(t_own_knowledge *ok)
{
	sem_post(ok->table->sem_forks);
	sem_post(ok->table->sem_forks);
}

void	eat(t_own_knowledge *ok)
{
	grab_forks(ok);
	sem_wait(ok->sem_last_meal);
	ok->t_last_meal = pprint(ok, "%04zu %d is eating\n");
	sem_post(ok->sem_last_meal);
	sleep_until(ok->t_last_meal + ok->table->t_eat);
	return_forks(ok);
}

void	rest(t_own_knowledge *ok)
{
	size_t	t;
	t = pprint(ok, "%04zu %d is sleeping\n");
	sleep_until(t + ok->table->t_sleep);
}
