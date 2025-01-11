#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int main()
{
	char *buffer;
	char rea[10];

	int rd_fd = open("tmp", O_CREAT | O_TRUNC | O_RDONLY , 0777);
	int wr_fd = open("tmp", O_WRONLY);
	unlink("tmp");
	while (1)
	{
		buffer = get_next_line(0);
		if (buffer[0] == '~')
			break;
		write(wr_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	int rd = read(rd_fd, rea, 9);
	while (rd)
	{
		rea[rd] = 0;
		printf("%s", rea);
		rd = read(rd_fd, rea, 9);
	}
	return (0);
}
