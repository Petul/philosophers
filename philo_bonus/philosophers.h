/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:24:03 by pleander          #+#    #+#             */
/*   Updated: 2024/09/16 11:26:28 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stddef.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>

# define START_DELAY 100
# define SEM_FORKS "sem_forks"
# define SEM_DEATH "sem_death"

typedef enum e_state
{
	THINKING = 1,
	EATING,
	SLEEPING,
	EXITED,
}	t_state;

typedef struct s_settings
{
	int		n_philos;
	int		n_eat;
	size_t	t_sleep;
	size_t	t_die;
	size_t	t_eat;
}	t_settings;

typedef struct s_table
{
	int				n_philos;
	int				n_eat;
	size_t			t_sleep;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sim_start;
	sem_t			*sem_forks;
	sem_t			*sem_death;
	sem_t			**sem_eaten_enough;
}	t_table;

typedef struct s_own_knowledge
{
	int						id;
	t_state					cs;
	ssize_t					t_last_meal;
	int						n_meals;
	sem_t					*sem_death;
	sem_t					*sem_eaten_enough;
	t_table					*table;
}	t_own_knowledge;

pthread_mutex_t	*create_forks(int n_forks);
int				ft_atoi(const char *str);
void			philo(t_own_knowledge *ok);
size_t			get_milliseconds(void);
int				run_simulation(t_table *table);
void			delay_start(t_own_knowledge *ok);
int				acquire_forks(t_own_knowledge *ok);
void			release_forks(t_own_knowledge *ok);
size_t			get_last_meal(t_own_knowledge *ok);
void			set_last_meal(t_own_knowledge *ok);
int				is_number(char	*str);
int				prepare_table(t_table *table, t_settings *s);

#endif
