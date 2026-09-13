/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:24:11 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/12 20:24:12 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	copy_data(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

t_stash	*stash_new(void)
{
	t_stash	*stash;

	stash = malloc(sizeof(t_stash));
	if (!stash)
		return (NULL);
	stash->data = malloc(2);
	if (!stash->data)
	{
		free(stash);
		return (NULL);
	}
	stash->len = 0;
	stash->capacity = 2;
	stash->has_nl = 0;
	stash->data[0] = '\0';
	return (stash);
}

int	stash_append(t_stash *stash, char *buf, size_t bytes)
{
	char	*new_data;
	size_t	new_cap;
	size_t	i;

	new_cap = stash->capacity;
	while (new_cap < stash->len + bytes + 1)
		new_cap *= 2;
	if (new_cap != stash->capacity)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (0);
		copy_data(new_data, stash->data, stash->len);
		free(stash->data);
		stash->data = new_data;
		stash->capacity = new_cap;
	}
	i = 0;
	while (i < bytes)
	{
		stash->data[stash->len++] = buf[i];
		stash->has_nl |= (buf[i++] == '\n');
	}
	stash->data[stash->len] = '\0';
	return (1);
}

void	*free_stash(t_stash *stash)
{
	if (stash)
	{
		free(stash->data);
		free(stash);
	}
	return (NULL);
}
