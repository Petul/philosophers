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
#include "philosophers.h"

size_t pprint(t_own_knowledge *ok, char *fstr)
{
	size_t	t;

	sem_wait(ok->table->sem_print);
	t = get_milliseconds();
	printf(fstr, t - ok->table->t_sim_start, ok->id);
	sem_post(ok->table->sem_print);
	return (t);
}

