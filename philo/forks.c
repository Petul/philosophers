/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:37:12 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:43:12 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
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
	memset(forks, 0, sizeof(pthread_mutex_t) * n_forks);
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
		if (is_sim_running(ok->table) != 1)
			return (-1);
		pthread_mutex_lock(&ok->table->take_forks_mtx);
		if (ok->mtx_fork1 != ok->mtx_fork2
			&& get_state(ok->left_philo) != EATING
			&& get_state(ok->right_philo) != EATING)
		{
			pthread_mutex_lock(ok->mtx_fork1);
			if (philo_print(ok, "%04zu %d has taken a fork\n", ok->id) < 0)
				return (-1);
			pthread_mutex_lock(ok->mtx_fork2);
			if (philo_print(ok, "%04zu %d has taken a fork\n", ok->id) < 0)
				return (-1);
			set_state(ok, EATING);
			increment_n_meals(ok);
			pthread_mutex_unlock(&ok->table->take_forks_mtx);
			return (0);
		}
		pthread_mutex_unlock(&ok->table->take_forks_mtx);
	}
}

void	release_forks(t_own_knowledge *ok)
{
	pthread_mutex_unlock(ok->mtx_fork1);
	pthread_mutex_unlock(ok->mtx_fork2);
	return ;
}
