/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:28:08 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 15:13:23 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_last_meal(t_own_knowledge *ok)
{
	size_t	t_last_meal;

	pthread_mutex_lock(&ok->mtx_last_meal);
	t_last_meal = ok->t_last_meal;
	pthread_mutex_unlock(&ok->mtx_last_meal);
	return (t_last_meal);
}

void	set_last_meal(t_own_knowledge *ok)
{
	pthread_mutex_lock(&ok->mtx_last_meal);
	ok->t_last_meal = get_milliseconds();
	pthread_mutex_unlock(&ok->mtx_last_meal);
}
