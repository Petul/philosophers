/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:07:39 by pleander          #+#    #+#             */
/*   Updated: 2024/09/05 14:36:26 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

static int	parse_args(int argc, char **argv, t_settings *s)
{
	s->n_philos = ft_atoi(argv[1]);
	if (s->n_philos < 1)
		return (-1);
	s->t_die = ft_atoi(argv[2]);
	s->t_eat = ft_atoi(argv[3]);
	s->t_sleep = ft_atoi(argv[4]);
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


static int	philo(t_settings *s, pthread_t *philosophers, pthread_mutex_t *forks)
{
	int				dead_mans_switch;
	pthread_mutex_t	dms_mutex;
	t_philosopher	*p;
	int				i;

	if (pthread_mutex_init(&dms_mutex, NULL) != 0)
		return (1);
	dead_mans_switch = 0;
	p = malloc(sizeof(t_philosopher) * s->n_philos);
	if (!p)
		return (1);
	i = 0;
	while (i < s->n_philos)
	{
		p[i].id = i;
		p[i].settings = s;
		p[i].dead_mans_switch = &dead_mans_switch;
		p[i].dms_mutex = &dms_mutex;
		p[i].fork1 = &forks[i];
		if (i + 1 >= s->n_philos)
			p[i].fork2 = &forks[0];
		else
			p[i].fork2 = &forks[i + 1];
		pthread_create(&philosophers[i], NULL, &philosopher, &p[i]);
		i++;
	}
	i = 0;
	while (i < s->n_philos)
	{
		pthread_join(philosophers[i], NULL); 
		i++;
	}
	
	pthread_mutex_destroy(&dms_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_settings		s;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number or arguments\n");
		return(1);
	}
	if (parse_args(argc, argv, &s) < 0)
		printf("Error: incorrect argument(s)\n");
	forks = create_forks(s.n_philos);
	if (!forks)
		return (1);
	philosophers = malloc(sizeof(pthread_t) * s.n_philos);
	if (!philosophers)
	{
		free(forks);
		return (1);
	}
	philo(&s, philosophers, forks);
}


