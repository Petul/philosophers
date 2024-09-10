/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:24:20 by pleander          #+#    #+#             */
/*   Updated: 2024/09/10 09:42:27 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philosophers.h"

int	philo_print(t_own_knowledge *ok, char *fstr, int id)
{
	if (pthread_mutex_lock(&ok->sk->print_mtx) < 0)
		return (-1);
	ok->t_cs_start = get_milliseconds();
	if (ok->t_cs_start < 0)
		return (-1);
	if (printf(fstr, ok->t_cs_start - ok->sk->t_sim_start, id) < 0)
		return (-1);
	if (pthread_mutex_unlock(&ok->sk->print_mtx) < 0)
		return (-1);
	return (0);
}
