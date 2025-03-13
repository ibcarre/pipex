/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:43:34 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/03/07 18:44:42 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	*buffer;
	char	rea[10];
	int		rd_fd;
	int		wr_fd;
	int		rd;

	rd_fd = open("tmp", O_CREAT | O_TRUNC | O_RDONLY, 0777);
	wr_fd = open("tmp", O_WRONLY);
	unlink("tmp");
	while (1)
	{
		buffer = get_next_line(0);
		if (buffer[0] == '~')
			break ;
		write(wr_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	rd = read(rd_fd, rea, 9);
	while (rd)
	{
		rea[rd] = 0;
		printf("%s", rea);
		rd = read(rd_fd, rea, 9);
	}
	return (0);
}
