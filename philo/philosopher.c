/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 14:45:05 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "philosophers.h"

void	*set_exit_and_return(t_own_knowledge *ok)
{
	if (get_state(ok) == EATING)
		release_forks(ok);
	set_state(ok, EXITED);
	return (NULL);
}

void	*philosopher(void *own_knowledge)
{
	t_own_knowledge			*ok;

	ok = (t_own_knowledge *)own_knowledge;
	if (delay_start(ok) < 0)
		return (NULL);
	while (1)
	{
		if (is_sim_running(ok->table) != 1)
			return (set_exit_and_return(ok));
		if (set_state(ok, THINKING) < 0)
			return (set_exit_and_return(ok));
		usleep(500);
		if (acquire_forks(ok) < 0)
			return (set_exit_and_return(ok));
		if (wait_or_exit(ok->table, ok->table->t_eat) != 0)
			return (set_exit_and_return(ok));
		if (release_forks(ok) < 0)
			return (set_exit_and_return(ok));
		if (set_state(ok, SLEEPING) < 0)
			return (set_exit_and_return(ok));
		if (wait_or_exit(ok->table, ok->table->t_sleep) != 0)
			return (set_exit_and_return(ok));
	}
	return (&ok->id);
}
