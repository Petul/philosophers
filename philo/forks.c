/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:37:12 by pleander          #+#    #+#             */
/*   Updated: 2024/09/13 14:45:19 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

void	destroy_forks(pthread_mutex_t *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

pthread_mutex_t	*create_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * n_forks);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);

}

int	acquire_forks(t_own_knowledge *ok)
{
	while (1)
	{
		pthread_mutex_lock(&ok->table->take_forks_mtx);
		if (get_state(ok->left_philo) != EATING
			&& get_state(ok->right_philo) != EATING)
		{
			pthread_mutex_lock(ok->mtx_fork1);
			if (philo_print(ok, "%04zu %d has taken a fork\n",  ok->id) < 0)
				return (-1);
			pthread_mutex_lock(ok->mtx_fork2);
			if (philo_print(ok, "%04zu %d has taken a fork\n",  ok->id) < 0)
				return (-1);
			set_state(ok, EATING);
			increment_n_meals(ok);
			pthread_mutex_unlock(&ok->table->take_forks_mtx);
			return (0);
		}
		pthread_mutex_unlock(&ok->table->take_forks_mtx);
	}
}

int	release_forks(t_own_knowledge *ok)
{
	if (pthread_mutex_unlock(ok->mtx_fork1) < 0)
		return (-1);
	if (pthread_mutex_unlock(ok->mtx_fork2) < 0)
		return (-1);
	return (0);
}
