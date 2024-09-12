/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_meals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:07:08 by pleander          #+#    #+#             */
/*   Updated: 2024/09/12 14:09:39 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	get_n_meals(t_own_knowledge *ok)
{
	int	n_meals;

	if (pthread_mutex_lock(&ok->mtx_last_meal) < 0)
		return (-1);
	n_meals = ok->n_meals;
	if (pthread_mutex_unlock(&ok->mtx_last_meal) < 0)
		return (-1);
	return (n_meals);
}

int	increment_n_meals(t_own_knowledge *ok)
{
	if (pthread_mutex_lock(&ok->mtx_last_meal) < 0)
		return (-1);
	ok->n_meals++;
	if (pthread_mutex_unlock(&ok->mtx_last_meal) < 0)
		return (-1);
	return (0);
}
