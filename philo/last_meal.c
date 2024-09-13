/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:28:08 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 10:10:56 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

ssize_t	get_last_meal(t_own_knowledge *ok)
{
	ssize_t	t_last_meal;

	if (pthread_mutex_lock(&ok->mtx_last_meal) != 0)
		return (-1);
	t_last_meal = ok->t_last_meal;
	if (pthread_mutex_unlock(&ok->mtx_last_meal) != 0)
		return (-1);
	return (t_last_meal);
}

ssize_t	set_last_meal(t_own_knowledge *ok)
{
	ssize_t t_last_meal;

	if (pthread_mutex_lock(&ok->mtx_last_meal) < 0)
		return (-1);
	t_last_meal = get_milliseconds();
	ok->t_last_meal = t_last_meal;
	if (pthread_mutex_unlock(&ok->mtx_last_meal) < 0)
		return (-1);
	return (t_last_meal);
}
