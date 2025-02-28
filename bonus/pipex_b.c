/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:05:06 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/02/24 17:13:00 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex_b.h"
#include <errno.h>

int	len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	execute(int in, int out, char **argc, char *env[])
{
	int		status;
	char	**cmd;
	char	*path;
	int		i;

	i = len(argc);
	status = 0;
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

int	pipex(int in, int out, char **argc, char *env[])
{
	int		child;
	int		i;
	int		pipeends[2];
	int		status;

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
	return (execute(in, out, argc, env));
}
