/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_knowledge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:36:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/09 10:37:14 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

void	destroy_shared_knowledge(t_shared_knowledge	*sk)
{
	pthread_mutex_destroy(&sk->sim_running_mtx);
	free(sk);
}

t_shared_knowledge	*create_shared_knowledge(t_settings *s)
{
	t_shared_knowledge	*sk;

	sk = malloc(sizeof(t_shared_knowledge));
	if (!sk)
		return (NULL);
	sk->t_sleep = s->t_sleep;
	sk->t_die = s->t_die;
	sk->t_eat = s->t_eat;
	sk->sim_running = 1;
	if (pthread_mutex_init(&sk->sim_running_mtx, NULL) < 0)
	{
		free(sk);
		return (NULL);
	}
	if (pthread_mutex_init(&sk->print_mtx, NULL) < 0)
	{
		free(sk);
		return (NULL);
	}
	return (sk);
}
