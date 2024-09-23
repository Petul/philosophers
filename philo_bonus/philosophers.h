/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:24:03 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:25:46 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stddef.h>
# include <semaphore.h>
# include <unistd.h>

# define SEM_FORKS "sem_forks"
# define SEM_DEATH "sem_death"
# define SEM_GRAB_FORKS "sem_grab_forks"
# define SEM_PRINT "sem_print"
# define SEM_SIM_ENDED "sem_sim_print"
# define SEM_EATEN_ENOUGH "sem_eaten_enough"

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
	int				died;
	int				eaten_enough;
	sem_t			*sem_forks;
	sem_t			*sem_death;
	sem_t			*sem_grab_forks;
	sem_t			*sem_print;
	sem_t			*sem_eaten_enough;
}	t_table;

typedef struct s_own_knowledge
{
	int						id;
	ssize_t					t_last_meal;
	int						n_meals;
	sem_t					*sem_death;
	sem_t					*sem_last_meal;
	t_table					*table;
}	t_own_knowledge;

int		ft_atoi(const char *str);
void	philo(t_own_knowledge *ok);
size_t	get_milliseconds(void);
int		run_simulation(t_table *table);
void	delay_start(t_own_knowledge *ok);
int		acquire_forks(t_own_knowledge *ok);
void	release_forks(t_own_knowledge *ok);
size_t	get_last_meal(t_own_knowledge *ok);
void	set_last_meal(t_own_knowledge *ok);
int		is_number(char	*str);
int		prepare_table(t_table *table, t_settings *s);
int		rest_or_die(t_own_knowledge *ok, size_t	msec);
size_t	pprint(t_own_knowledge *ok, char *fstr);
char	*make_sem_name(char *basename, size_t id);
void	sleep_until(size_t tn);
void	think(t_own_knowledge *ok);
void	eat(t_own_knowledge *ok);
void	rest(t_own_knowledge *ok);
void	*ft_memset(void *b, int c, size_t len);
void	init_philo(t_own_knowledge *ok, t_table *t);
void	kill_philos(pid_t *children);
int		init_philo_semaphores(t_own_knowledge *ok);
void	meal_monitor(t_table *t);

#endif
