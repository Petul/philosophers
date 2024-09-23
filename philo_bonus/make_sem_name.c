/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_sem_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:17 by pleander          #+#    #+#             */
/*   Updated: 2024/09/23 11:30:23 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_len(size_t id)
{
	size_t	len;

	len = 1;
	while (id > 9)
	{
		len++;
		id = id / 10;
	}
	return (len);
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

static void	ft_itoa(char *name, size_t *i, size_t id)
{
	if (id > 9)
	{
		ft_itoa(name, i, id / 10);
	}
	name[*i] = (id % 10) + '0';
	(*i)++;
}

char	*make_sem_name(char *basename, size_t id)
{
	size_t	id_len;
	size_t	i;
	char	*name;

	id_len = count_len(id);
	name = malloc(sizeof(char) * (ft_strlen(basename) + id_len + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (basename[i])
	{
		name[i] = basename[i];
		i++;
	}
	ft_itoa(name, &i, id);
	name[i] = 0;
	return (name);
}
