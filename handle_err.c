/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:42:23 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/08 14:13:35 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		return (perror("WRONG COMMAND "), errno); 
	return (errno);
}
