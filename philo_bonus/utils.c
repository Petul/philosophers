/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:29:42 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

size_t	get_milliseconds(void)
{
	struct timeval	tv;
	size_t			millis;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (millis);
}

void	delay_start(t_own_knowledge *ok)
{
	size_t	t;

	t = get_milliseconds();
	while (t < ok->table->t_sim_start)
		t = get_milliseconds();
}

int	is_number(char	*str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

void	sleep_until(size_t tn)
{
	size_t	t;

	t = get_milliseconds();
	while (t < tn)
	{
		usleep(100);
		t = get_milliseconds();
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;	
	size_t			i;
	size_t			qword_value;

	p = (unsigned char *)b;
	i = 0;
	while (i < sizeof(size_t))
	{
		qword_value = (qword_value << 8) | (unsigned char)c;
		i++;
	}
	while (len >= sizeof(size_t))
	{
		*(size_t *)p = qword_value;
		p += sizeof(size_t);
		len -= sizeof(size_t);
	}
	while (len > 0)
	{
		*p = (unsigned char)c;
		p++;
		len--;
	}
	return (b);
}
