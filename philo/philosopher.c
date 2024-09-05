/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:07:07 by pleander          #+#    #+#             */
/*   Updated: 2024/09/05 14:30:12 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "philosophers.h"

void	*philosopher(void *philosopher)
{
	t_philosopher	*p;
	uint8_t	eating;
	uint8_t	sleeping;
	uint8_t	thinking;

	p = (t_philosopher *)philosopher;
	printf("Hello from philosopher %d!\n", p->id);
	pthread_exit(0);
	eating = 0;
	sleeping = 0;
	thinking = 0;
	return (NULL);
}
