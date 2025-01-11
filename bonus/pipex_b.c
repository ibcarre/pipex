/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:05:06 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 20:03:39 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"
#include <errno.h>

int	ft_find(char *str, char *tofind)
{
	int	i;

	i = 0;
	while (str[i] == tofind[i] && tofind[i])
		i++;
	if (str[i] == 0 && tofind[i] == 0)
		return (1);
	return (0);
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

int	main(int argv, char **argc, char *env[])
{
	int	in_fd;
	int	out_fd;

	if (argv < 5)
		return (handle_err(1));
	in_fd = open(argc[1], O_RDONLY);
	if (in_fd < 0)
		return (handle_err(2));
	out_fd = open(argc[argv - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
		return (close(in_fd), handle_err(2));
	argc[argv - 1] = 0;
	if (ft_find(argc[1], "here_doc"))
		return (ft_heredoc(&argc[2], env, in_fd, out_fd));
	return (pipex(in_fd, out_fd, &argc[2], env));
}
