/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:05:06 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/10 22:05:10 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"

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
