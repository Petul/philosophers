#ifndef PHILOSOPHERS
# define PHILOSOPHERS

#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stddef.h>
#include <pthread.h>

#define START_DELAY 100

typedef enum e_state
{
	THINKING = 1,
	EATING,
	SLEEPING,
	EXITED,
} t_state;

typedef struct s_settings
{
	int	n_philos;
	int	n_eat;
	size_t	t_sleep;
	size_t	t_die;
	size_t	t_eat;
}	t_settings;

typedef	struct	s_table
{
	int				n_philos;
	int				n_eat;
	size_t			t_sleep;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sim_start;
	uint8_t			sim_running;
	pthread_mutex_t	sim_running_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	take_forks_mtx;
	pthread_mutex_t	*mtx_forks;
	pthread_t		*th_philos;
}	t_table;

typedef struct s_own_knowledge
{
	int						id;
	t_state					cs;
	ssize_t					t_last_meal;
	int						n_meals;
	pthread_mutex_t			mtx_n_meals;
	pthread_mutex_t			mtx_last_meal;
	pthread_mutex_t			mtx_state;
	pthread_mutex_t			*mtx_fork1;
	pthread_mutex_t			*mtx_fork2;
	struct s_own_knowledge	*left_philo;
	struct s_own_knowledge	*right_philo;
	t_table					*table;
}	t_own_knowledge;


int	ft_atoi(const char *str);
pthread_mutex_t	*create_forks(int n_forks);
void	destroy_forks(pthread_mutex_t *forks, int n_forks);
void		*philo(void *philosopher);
ssize_t		get_milliseconds(void);
int	run_simulation(t_table *table, t_own_knowledge *ok);
int	philo_print(t_own_knowledge *ok, char *fstr, int id);
int	print_eat(t_own_knowledge *ok);
int	print_died(t_own_knowledge *ok, int id, size_t t_death);
int	wait_or_exit(t_table *table, size_t	msec);
int	is_sim_running(t_table *table);
int	delay_start(t_own_knowledge *ok);
int	increment_n_meals(t_own_knowledge *ok);
int	get_n_meals(t_own_knowledge *ok);
t_state	get_state(t_own_knowledge *ok);
int	set_state(t_own_knowledge *ok, t_state state);
int	acquire_forks(t_own_knowledge *ok);
int	release_forks(t_own_knowledge *ok);
ssize_t	get_last_meal(t_own_knowledge *ok);
ssize_t	set_last_meal(t_own_knowledge *ok);
int	is_number(char	*str);
int	prepare_table(t_table *table, t_settings *s, pthread_mutex_t *mtx_forks, pthread_t *th_philos);

#endif
