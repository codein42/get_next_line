/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:22:21 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/12 20:32:04 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_stash	**find_stash(t_stash **list, int fd)
{
	t_stash	**cur;

	cur = list;
	while (*cur && (*cur)->fd != fd)
		cur = &(*cur)->next;
	return (cur);
}

static t_stash	*fill_stash(int fd, t_stash *stash)
{
	char		*buf;
	ssize_t		n;

	if (!stash)
		stash = stash_new(fd);
	if (!stash)
		return (free_stash(stash));
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free_stash(stash));
	n = 1;
	while (n > 0 && !stash->has_nl)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0 || !stash_append(stash, buf, (size_t)n))
		{
			free(buf);
			return (free_stash(stash));
		}
	}
	free(buf);
	if (!stash->len)
		return (free_stash(stash));
	return (stash);
}

static char	*take_line(t_stash *stash, size_t *used)
{
	size_t	i;
	char	*line;

	i = 0;
	while (i < stash->len && stash->data[i] != '\n')
		i++;
	if (i < stash->len)
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	*used = i;
	while (i--)
		line[i] = stash->data[i];
	line[*used] = '\0';
	return (line);
}

static t_stash	*update_stash(t_stash *stash, size_t used)
{
	t_stash	*rest;
	t_stash	*next;

	next = stash->next;
	if (used == stash->len)
	{
		free_stash(stash);
		return (next);
	}
	rest = stash_new(stash->fd);
	if (!rest || !stash_append(rest, &stash->data[used], stash->len - used))
	{
		free_stash(rest);
		free_stash(stash);
		return (next);
	}
	rest->next = next;
	free_stash(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static t_stash	*list;
	t_stash			**slot;
	t_stash			*stash;
	char			*line;
	size_t			used;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	slot = find_stash(&list, fd);
	stash = fill_stash(fd, *slot);
	*slot = stash;
	if (!stash)
		return (NULL);
	line = take_line(stash, &used);
	if (!line)
	{
		*slot = free_stash(stash);
		return (NULL);
	}
	*slot = update_stash(stash, used);
	return (line);
}
