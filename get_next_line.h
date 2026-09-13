/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:24:49 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/12 20:25:08 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_stash
{
	char	*data;
	size_t	len;
	size_t	capacity;
	int		has_nl;
}	t_stash;

char	*get_next_line(int fd);
t_stash	*stash_new(void);
int		stash_append(t_stash *stash, char *buf, size_t bytes);
void	*free_stash(t_stash *stash);

#endif
