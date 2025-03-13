/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:34:28 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/03/13 15:10:40 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split(char *str, char sep);
char	*ft_strjoin(char *str, char *str2);
int		handle_err(int err);
void	ft_free(char **str);
char	*findpath(char *cmd, char *env[]);
int		ft_find(char *str, char *str2);
int     ft_strlen(char *str);

#endif
