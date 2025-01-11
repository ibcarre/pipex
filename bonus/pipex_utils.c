/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:42:23 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 19:25:26 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"

int	handle_err(int errno)
{
	if (errno == 1)
	{
		write(2, "WRONG USAGE\n", 13);
		return (errno);
	}
	if (errno == 2)
	{
		write(2, "ERROR OPENING\n", 14);
		return (errno);
	}
	if (errno == 3)
		return (write(2, "PATH ERROR\n", 11), errno);
	if (errno == 4)
		return (write(2, "PIPE ERROR\n", 11), errno);
	if (errno == 5)
		return (write(2, "FORK ERROR\n", 11), errno);
	if (errno == 6)
		return (write(2, "WRONG COMMAND\n", 14), errno);
	return (errno);
}

static char	**ft_getpath(char *env[])
{
	int		i;
	int		j;
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

char	*findpath(char *cmd, char *env[])
{
	char	**paths;
	int		i;
	char	*path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	paths = ft_getpath(env);
	if (!paths)
		return (NULL);
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
