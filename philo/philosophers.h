#ifndef PHILOSOPHERS
# define PHILOSOPHERS

#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stddef.h>
#include <pthread.h>

#define START_DELAY 10

typedef enum e_state
{
	THINK = 1,
	EAT,
	SLEEP,
} t_state;

typedef struct s_settings
{
	int	n_philos;
	int	n_eat;
	size_t	t_sleep;
	size_t	t_die;
	size_t	t_eat;
}	t_settings;

typedef struct s_shared_knowledge
{
	size_t				t_sleep;
	size_t				t_die;
	size_t				t_eat;
	size_t				t_sim_start;
	uint8_t				sim_running;
	pthread_mutex_t		sim_running_mtx;
	pthread_mutex_t		print_mtx;

}	t_shared_knowledge;

typedef struct s_own_knowledge
{
	int					id;
	t_state				cs;
	size_t				t_cs_start;
	size_t				t_last_meal;
	pthread_mutex_t		mtx_last_meal;
	pthread_mutex_t		*mtx_fork1;
	pthread_mutex_t		*mtx_fork2;
	t_shared_knowledge	*sk;
}	t_own_knowledge;

typedef	struct	s_table
{
	int				n_philos;
	pthread_t		*th_philos;
	pthread_mutex_t	*mtx_forks;
}	t_table;

int	ft_atoi(const char *str);
pthread_mutex_t	*create_forks(int n_forks);
void	destroy_forks(pthread_mutex_t *forks, int n_forks);
void		*philosopher(void *philosopher);
ssize_t		get_milliseconds(void);
void	destroy_shared_knowledge(t_shared_knowledge	*sk);
t_shared_knowledge	*create_shared_knowledge(t_settings *s);
int	run_simulation(t_table *table, t_own_knowledge *ok);

#endif
