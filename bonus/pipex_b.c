/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:05:06 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 20:05:01 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"
#include "get_next_line.h"
#include <errno.h>

int	ft_find(char *str, char *tofind)
{
	int	i;

	i = 0;
	while (str[i] == tofind[i] && tofind[i] && str[i])
		i++;
	/*if (str[i] == 0 && tofind[i] == 0)
		return (1);
	return (0);*/
	if (str[i] == '\n' && str[i+1] == 0)
		return (0);
	return (str[i] - tofind[i]);
}

void	ft_close(int pipee[2], int in, int out)
{
	close(pipee[0]);
	close(in);
	close(out);
	close(pipee[1]);
}

int	child_in(int in, int pipeends[2], char *argc, char *env[])
{
	char	*path;
	char	**cmd;

	if (in != pipeends[0])
	{
		close(pipeends[0]);
		if (dup2(in, STDIN_FILENO) == -1)
			return (perror("DUP FAILED A"), errno);
	}
	close(in);
	if (dup2(pipeends[1], STDOUT_FILENO) == -1)
		return (perror("DUP FAILED B"), errno);
	close(pipeends[1]);
	cmd = ft_split(argc, ' ');
	if (!cmd)
		return (handle_err(6));
	path = findpath(cmd[0], env);
	if (!path)
		return (ft_free(cmd), handle_err(6));
	execve(path, cmd, env);
	free(path);
	ft_free(cmd);
	return (perror("EXECVE FAILED"), errno);
}

int	pipex(int in, int out, char **argc, char *env[])
{
	int child;
	int	i;
	char	*path;
	char	**cmd;
	int	pipeends[2];
	int status;

	i = 0;
	while (argc[i + 1])
	{
		if (pipe(pipeends) == -1)
			return (close(in), close(out), perror("FAILED PIPE"), errno);
		child = fork();
		if (child == 0 && i == 0)
			exit(child_in(in, pipeends, argc[i], env));
		else if (child == 0 && i != 0)
			exit(child_in(pipeends[0], pipeends, argc[i], env));
		else if (child == -1)
			return (ft_close(pipeends, in, out), perror("FAILED FORK"), errno);
		close(pipeends[1]);
		dup2(pipeends[0], STDIN_FILENO);
		waitpid(child, &status, 0);
		i++;
	}
	if (dup2(out, STDOUT_FILENO) == -1)
		return (perror("DUP FAILED C"), errno);
	cmd = ft_split(argc[i], ' ');
	if (!cmd)
		return (close(in), close(out), handle_err(6));
	path = findpath(cmd[0], env);
	if (!path)
		return (ft_free(cmd), close(in), close(out), handle_err(6));
	execve(path, cmd, env);
	return (status);
}

int	ft_heredoc(char **argc, char *env[], int out_fd)
{
	char	*buffer;
	int rd_fd;
	int wr_fd; 

	rd_fd = open("tmp", O_CREAT | O_TRUNC | O_RDONLY , 0644);
	wr_fd = open("tmp", O_WRONLY);
	unlink("tmp");
	while(1)
	{
		buffer = get_next_line(0);
		if (ft_find(buffer, argc[0]) == 0)
		{
			free(buffer);
			break;
		}
		write(wr_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(wr_fd);
	return (pipex(rd_fd, out_fd, &argc[1], env));
}

int	main(int argv, char **argc, char *env[])
{
	int	in_fd;
	int	out_fd;

	if (argv < 5)
		return (handle_err(1));
	out_fd = open(argc[argv - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
		return (handle_err(2));
	argc[argv - 1] = 0;
	if (ft_find(argc[1], "here_doc") == 0)
		return (ft_heredoc(&argc[2], env, out_fd));
	in_fd = open(argc[1], O_RDONLY);
	if (in_fd < 0)
		return (close(out_fd), handle_err(2));
	return (pipex(in_fd, out_fd, &argc[2], env));
}
