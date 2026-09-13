/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 20:41:45 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/12 21:25:57 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = 4;
	if (fd < 0)
		return (1);

	printf("FD = %d\n\n", fd);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

