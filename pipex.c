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

}

int	child_in(int in, int pipeEnds[2], char *env[], char **argc)
{
	char	*path;

	if (dup2(in, 0) == - 1)
		return (perror("DUP FAILED"), -1);
	close(in);
	if (dup2(pipeEnds[1], 1 == -1))
		return (perror("DUP FAILED"), -1);
	close(pipeEnds[1]);
	path = findpath(argc[0], env);
	execve(path, ft_split(argc[0]), env);
	perror("EXECVE FAILED");
	return (-1);
}

int	child_out(int out, int pipeEnds[2], char *env[], char **argc)
{
	
}

int	pipex(int in, int out, char **argc, char *env[])
{
	int	pipeEnds[2];
	int	childO;
	int	status;

	if (pipe(pipeEnds) == -1)
		return (close(in), close(out), handle_err(4));
	childO = fork();
	if (child0 == 0)
	{
		if (child_in(in, pipeEnds, env, argc) == -1)
			exit(close(in), close(out), -1);
		exit(0);
	}
	else if (childO == -1)
		return (close(in), close(out), handle_err(5));
	childT = fork();
	if (childT == 0)
	{
		if(child_out(out, pipeEnds, env, argc) == -1)
			exit(close(in), close(out), -1);
		exit(0);
	}
	else if (childT == -1)
		return (close(in), close(out), handle_err(5));
	return (waitpid(childT, &status, 0), status);
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
	if (out_fd < 0)
		return (close(in_fd), handle_err(2));
	return (pipex(in_fd, out_fd, argc, env));
}
