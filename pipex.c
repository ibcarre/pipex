/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:21:05 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/08 18:49:46 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getpath(char *env[])
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	str = "PATH";
	while (env[i])
	{
		while (env[i][j] == str[j])
		{
			j++;
			if (j == 4)
				return (ft_split(&env[i][4], ':'));
		}
		i++;
		j = 0;
	}
	return (NULL);
}

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

char	*findpath(char *cmd, char *env[])
{
	char	**paths;
	int	i;
	char	*path;

	paths = ft_getpath(env);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(path, F_OK) == 0)
			return (ft_free(paths), path);
		free(path);
		i++;
	}
	return (ft_free(paths), NULL);
}

int	child_in(int in, int pipeEnds[2], char *env[], char **argc)
{
	char	*path;
	char	**cmd;

	if (dup2(in, 0) == - 1)
		return (perror("DUP FAILED"), -1);
	close(in);
	close(pipeEnds[0]);
	if (dup2(pipeEnds[1], 1) == -1)
		return (perror("DUP FAILED"), -1);
	close(pipeEnds[1]);
	cmd = ft_split(argc[0], ' ');
	if (!cmd)
		return (free(path), handle_err(6), -1);
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
	if (dup2(pipeEnds[0], 0) == -1)
		return (perror("DUP FAILED"), -1);
	close(pipeEnds[0]);
	if (dup2(out, 1) == -1)
		return (perror("DUP FAILED"), -1);
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

int	pipex(int in, int out, char **argc, char *env[])
{
	int	pipeEnds[2];
	int	childO;
	int	status;
	int	child;

	if (pipe(pipeEnds) == -1)
		return (close(in), close(out), handle_err(4));
	childO = fork();
	if (childO == 0)
	{
		if (child_in(in, pipeEnds, env, argc) == -1)
			exit(-1);
		exit(0);
	}
	else if (childO == -1)
		return (close(in), close(out), handle_err(5));
	child = fork();
	if (child == 0)
	{
		if(child_out(out, pipeEnds, env, argc) == -1)
			exit(-1);
		exit(0);
	}
	else if (child == -1)
		return (close(in), close(out), handle_err(5));
	return (0);
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
	out_fd = open(argc[argv - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	argc[argv - 1] = 0;
	argc[3] = argc[argv - 2];
	if (out_fd < 0)
		return (close(in_fd), handle_err(2));
	return (pipex(in_fd, out_fd, &argc[2], env));
}
