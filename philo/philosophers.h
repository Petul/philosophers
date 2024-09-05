#ifndef PHILOSOPHERS
# define PHILOSOPHERS

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>

typedef struct s_settings
{
	int	n_philos;
	int	n_eat;
	int	t_sleep;
	int	t_die;
	int	t_eat;
}	t_settings;

typedef struct s_philosopher
{
	int				id;
	t_settings		*settings;
	int				*dead_mans_switch;
	pthread_mutex_t	*dms_mutex;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philosopher;


int	ft_atoi(const char *str);
pthread_mutex_t	*create_forks(int n_forks);
void	destroy_forks(pthread_mutex_t *forks, int n_forks);
void		*philosopher(void *philosopher);

#endif
