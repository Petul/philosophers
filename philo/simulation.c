/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:46:26 by pleander          #+#    #+#             */
/*   Updated: 2024/09/09 13:01:29 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	run_simulation(t_table *table, t_own_knowledge *ok)
{
	int		i;

	ok->sk->t_sim_start = get_milliseconds();
	if (ok->sk->t_sim_start < 0)
		return (-1);
	ok->sk->t_sim_start += START_DELAY;
	i = 0;
	while (i < table->n_philos)
	{
		ok[i].t_cs_start = ok->sk->t_sim_start;
		ok[i].t_last_meal = ok->sk->t_sim_start;
		pthread_create(&table->th_philos[i], NULL, &philosopher, &ok[i]); // Handle failure
		i++;
	}
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->th_philos[i], NULL); 
		i++;
	}
	return (0);
}
