/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/10 10:00:32 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philosophers.h"

static int	delay_start(t_own_knowledge *ok)
{
	ssize_t	t;

	t = get_milliseconds();
	if (t < 0)
		return (-1);
	while ((size_t)t < ok->sk->t_sim_start)
	{
		t = get_milliseconds();
		if (t < 0)
			return (-1);
	}
	return (1);
}

// static void *error_exit(void)
// {
// 	printf("Error\n");
// 	return (NULL);
// }

t_state	get_state(t_own_knowledge *ok)
{
	t_state	s;

	pthread_mutex_lock(&ok->mtx_state);
	s = ok->cs;
	pthread_mutex_unlock(&ok->mtx_state);
	return (s);
}

void	set_state(t_own_knowledge *ok, t_state state)
{
	pthread_mutex_lock(&ok->mtx_state);
	ok->cs = state;
	pthread_mutex_unlock(&ok->mtx_state);
}

int	acquire_forks(t_own_knowledge *ok)
{
	while (1)
	{
		pthread_mutex_lock(&ok->sk->take_forks_mtx);
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
			pthread_mutex_unlock(&ok->sk->take_forks_mtx);
			return (0);
		}
		pthread_mutex_unlock(&ok->sk->take_forks_mtx);
	}
}

void	release_forks(t_own_knowledge *ok)
{
	pthread_mutex_unlock(ok->mtx_fork1);
	pthread_mutex_unlock(ok->mtx_fork2);
}

void	*philosopher(void *own_knowledge)
{
	t_own_knowledge			*ok;

	ok = (t_own_knowledge *)own_knowledge;
	if (delay_start(ok) < 0)
		return (NULL);
	while (1)
	{
		set_state(ok, THINKING);
		if (philo_print(ok, "%04zu %d is thinking\n", ok->id) < 0)
			return (NULL); //set error flag?
		usleep(500);
		if (acquire_forks(ok) < 0)
			return (NULL);
		if (philo_print(ok, "%04zu %d is eating\n", ok->id) < 0)
			return (NULL);
		usleep(ok->sk->t_eat);
		release_forks(ok);
		set_state(ok, SLEEPING);
		if (philo_print(ok, "%04zu %d is sleeping\n", ok->id) < 0)
			return (NULL);
		usleep(ok->sk->t_sleep);
	}
	pthread_exit(0);
}
