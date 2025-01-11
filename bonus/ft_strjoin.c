/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:14:34 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 19:51:43 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *str2)
{
	char	*str3;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) + ft_strlen(str2);
	str3 = malloc(len + 1);
	str3[len] = 0;
	while (str[i])
	{
		str3[i] = str[i];
		i++;
	}
	while (str2[j])
	{
		str3[i] = str2[j];
		i++;
		j++;
	}
	return (str3);
}
