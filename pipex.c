/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:21:05 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 19:29:25 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_in(int in, int pipeEnds[2], char *env[], char **argc)
{
	char	*path;
	char	**cmd;

	if (dup2(in, STDIN_FILENO) == -1)
		return (close(in), perror("DUP FAILED A"), -1);
	close(in);
	close(pipeEnds[0]);
	if (dup2(pipeEnds[1], STDOUT_FILENO) == -1)
		return (close(pipeEnds[1]), perror("DUP FAILED B"), -1);
	close(pipeEnds[1]);
	cmd = ft_split(argc[0], ' ');
	if (!cmd)
		return (handle_err(6), -1);
	path = findpath(cmd[0], env);
	if (!path)
		return (handle_err(6), -1);
	execve(path, cmd, env);
	free(path);
	ft_free(cmd);
	perror("EXECVE FAILED");
	return (-1);
}

int	child_out(int out, int pipeEnds[2], char *env[], char **argc)
{
	char	*path;
	char	**cmd;

	close(pipeEnds[1]);
	if (dup2(pipeEnds[0], STDIN_FILENO) == -1)
		return (close(out), close(pipeEnds[0]), perror("DUP FAILED C"), -1);
	close(pipeEnds[0]);
	if (dup2(out, STDOUT_FILENO) == -1)
		return (close(out), perror("DUP FAILED D"), -1);
	close(out);
	cmd = ft_split(argc[1], ' ');
	if (!cmd)
		return (handle_err(6), -1);
	path = findpath(cmd[0], env);
	if (!path)
		return (free(cmd), handle_err(6), -1);
	execve(path, cmd, env);
	free(path);
	ft_free(cmd);
	perror("EXECVE FAILED");
	return (-1);
}

void	ft_close(int pipeends[2], int in, int out)
{
	close(pipeends[0]);
	close(pipeends[1]);
	close(in);
	close(out);
}

int	pipex(int in, int out, char **argc, char *env[])
{
	int	pipeends[2];
	int	childo;
	int	childt;
	int	status;

	if (pipe(pipeends) == -1)
		return (close(in), close(out), handle_err(4));
	childo = fork();
	if (childo == 0)
	{
		close(out);
		exit(child_in(in, pipeends, env, argc));
	}
	else if (childo == -1)
		return (ft_close(pipeends, in, out), handle_err(5));
	childt = fork();
	if (childt == 0)
	{
		close(in);
		exit(child_out(out, pipeends, env, argc));
	}
	else if (childt == -1)
		return (ft_close(pipeends, in, out), handle_err(5));
	ft_close(pipeends, in, out);
	return (waitpid(childo, &status, 0), waitpid(childt, &status, 0), status);
}

int	main(int argv, char **argc, char *env[])
{
	int	in_fd;
	int	out_fd;

	if (argv != 5)
		return (handle_err(1));
	in_fd = open(argc[1], O_RDONLY);
	if (in_fd < 0)
		return (handle_err(2));
	out_fd = open(argc[argv - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	argc[argv - 1] = 0;
	if (out_fd < 0)
		return (close(in_fd), handle_err(2));
	return (pipex(in_fd, out_fd, &argc[2], env));
}
