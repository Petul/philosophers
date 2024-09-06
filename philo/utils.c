/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:28:45 by pleander          #+#    #+#             */
/*   Updated: 2024/09/06 11:38:35 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/types.h>
#include <stdlib.h>
#include <sys/time.h>

ssize_t	get_milliseconds(void)
{
	struct timeval	tv;
	size_t			millis;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (millis);
}
