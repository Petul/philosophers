#ifndef PHILOSOPHERS
# define PHILOSOPHERS

#include <stddef.h>

typedef struct s_settings
{
	int	n_philos;
	int	n_eat;
	int	t_sleep;
	int	t_die;
	int	t_eat;
}	t_settings;

int	ft_atoi(const char *str);

#endif
