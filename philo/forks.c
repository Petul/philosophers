/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:37:12 by pleander          #+#    #+#             */
/*   Updated: 2024/09/05 14:14:46 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

void	destroy_forks(pthread_mutex_t *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

pthread_mutex_t	*create_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * n_forks);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);

}
