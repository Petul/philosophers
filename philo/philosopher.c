/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/12 14:11:13 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "philosophers.h"


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
			increment_n_meals(ok);
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
	int						res;

	ok = (t_own_knowledge *)own_knowledge;
	if (delay_start(ok) < 0)
		return (NULL);
	while (1)
	{
		res = is_sim_running(ok->sk);
		if (res == 0)
			break ;
		if (res == -1)
			break ; //set early exit flag
		set_state(ok, THINKING);
		if (philo_print(ok, "%04zu %d is thinking\n", ok->id) < 0)
			break ; //set error flag?
		if (acquire_forks(ok) < 0)
			break ;
		if (print_eat(ok) < 0)
			break ;
		res = wait_or_exit(ok->sk, ok->sk->t_eat);
		if (res < 0)
			break ; // Set early exit error flag
		if (res > 1)
			break ;
		release_forks(ok);
		set_state(ok, SLEEPING);
		if (philo_print(ok, "%04zu %d is sleeping\n", ok->id) < 0)
			break ;
		res = wait_or_exit(ok->sk, ok->sk->t_sleep);
		if (res < 0)
			break ; // Set early exit error flag
		if (res > 1)
			break ;
	}
	int id = ok->id;
	return (&id);
}
