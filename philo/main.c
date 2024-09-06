/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/06 15:26:47 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	s->n_philos = ft_atoi(argv[1]);
	if (s->n_philos < 1)
		return (-1);
	s->t_die = (size_t)ft_atoi(argv[2]);
	s->t_eat = (size_t)ft_atoi(argv[3]);
	s->t_sleep = (size_t)ft_atoi(argv[4]);
	if (s->t_die < 0 || s->t_eat < 0 || s->t_sleep < 0)
		return (-1);
	if (argc == 6)
	{
		s->n_eat = ft_atoi(argv[5]);
		if (s->n_eat < 0)
			return (-1);
	}
	else
		s->n_eat = -1;
	return (0);
}

// static void	init_philosopher_memory(t_philosopher_memory *m, t_settings *s, pthread_mutex_t *forks)
// {
// 		if (m->id % 2)
// 			m->state = THINKING;
// 		else
// 			m->state = EATING;
// 		m->settings = s;
// 		m->fork1 = &forks[m->id];
// 		if (m->id + 1 >= s->n_philos)
// 			m->fork2 = &forks[0];
// 		else
// 			m->fork2 = &forks[m->id + 1];
// 		m->state_start_time = 0;
// 		m->sim_start_time = get_milliseconds();
// 		m->last_meal = m->sim_start_time;
// }

// static	int	watch_philosophers(t_philosopher_memory *m, int n_philos)
// {
// 	int	i;
//
// 	i = 0;
//
// }
// static int	philo(t_settings *s, pthread_t *philosophers, pthread_mutex_t *forks)
// {
// 	t_philosopher_memory	*p;
// 	int				i;
// 	ssize_t			sim_start_time;
// 	uint8_t			sim_running;
// 	pthread_mutex_t	sim_running_mtx;
//
// 	sim_running = 1;
// 	if (pthread_mutex_init(&sim_running_mtx, NULL) != 0)
// 		return (1);
// 	p = malloc(sizeof(t_philosopher_memory) * s->n_philos);
// 	if (!p)
// 		return (1);
// 	i = 0;
// 	sim_start_time = get_milliseconds();
// 	if (sim_start_time < 0)
// 	{
// 		free(p);
// 		return (1);
// 	}
// 	while (i < s->n_philos)
// 	{
// 		p[i].id = i;
// 		p[i].sim_start_time = sim_start_time;
// 		p[i].sim_running  = &sim_running;
// 		p[i].sim_running_mtx = &sim_running_mtx;
// 		init_philosopher_memory(&p[i], s, forks);
// 		pthread_create(&philosophers[i], NULL, &philosopher, &p[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < s->n_philos)
// 	{
// 		pthread_join(philosophers[i], NULL); 
// 		i++;
// 	}
// 	return (0);
// }

t_table	*prepare_table(t_settings *s)
{

}

static int	philosophers(t_settings s)
{
	t_table	*table;


}
int	main(int argc, char **argv)
{
	pthread_t		*th_philos;
	pthread_mutex_t	*mtx_forks;
	t_settings		s;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number or arguments\n");
		return(1);
	}
	if (parse_args(argc, argv, &s) < 0)
		printf("Error: incorrect argument(s)\n");
	mtx_forks = create_forks(s.n_philos);
	if (!mtx_forks)
		return (1);
	th_philos = malloc(sizeof(pthread_t) * s.n_philos);
	if (!th_philos)
	{
		free(mtx_forks);
		return (1);
	}
	philosophers(s);
}


