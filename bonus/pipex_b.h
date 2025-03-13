/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:34:28 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/03/07 18:45:19 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_B_H
# define PIPEX_B_H

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
char	*get_next_line(int fd);
int		pipex(int in, int out, char **argc, char *env[]);
int		child_in(int in, int pipeends[2], char *argc, char *env[]);
void	ft_close(int pipee[2], int in, int out);

#endif