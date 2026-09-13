/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainB.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 20:41:45 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/12 21:18:37 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("test_file1.txt", O_RDONLY);
	fd2 = open("test_file2.txt", O_RDONLY);
	fd3 = open("test_file3.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);

	printf("FD1 = %d\n", fd1);
	printf("FD2 = %d\n", fd2);
	printf("FD3 = %d\n\n", fd3);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
