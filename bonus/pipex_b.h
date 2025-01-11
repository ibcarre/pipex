/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:34:28 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 22:21:32 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

char	**ft_split(char *str, char sep);
char	*ft_strjoin(char *str, char *str2);
int		handle_err(int err);
void	ft_free(char **str);
char	*findpath(char *cmd, char *env[]);
char	*get_next_line(int fd);

#endif
