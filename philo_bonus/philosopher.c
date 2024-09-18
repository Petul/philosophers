/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:11:32 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include "philosophers.h"

static void	think(t_own_knowledge *ok)
{
	size_t	t;

	t = get_milliseconds() - ok->table->t_sim_start;
	printf("%04zu %d is thinking\n", t, ok->id);
	ok->cs = THINKING;
}

void	philo(t_own_knowledge *ok)
{
	delay_start(ok);
	while (1)
	{
		think(ok);
		usleep(500);
		return ;
		// if (acquire_forks(ok) < 0)
		// 	return (set_exit_and_return(ok));
		// if (wait_or_exit(ok->table, ok->table->t_eat) != 0)
		// 	return (set_exit_and_return(ok));
		// release_forks(ok);
		// if (set_state(ok, SLEEPING) < 0)
		// 	return (set_exit_and_return(ok));
		// if (wait_or_exit(ok->table, ok->table->t_sleep) != 0)
		// 	return (set_exit_and_return(ok));
	}
}
