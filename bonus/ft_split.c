/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:02:48 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/01/11 19:51:50 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_b.h"

static int	count_words(char *str, char sep)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (str[0] == 0)
		return (count);
	if (str[0] != sep)
		count++;
	while (str[i])
	{
		if (str[i - 1] == sep && str[i] != sep)
			count++;
		i++;
	}
	return (count);
}

static void	ft_frees(char **res, int i)
{
	i--;
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
}

static void	initialize(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

static char	**ft_mal(char **res, char *str, char sep)
{
	int		i;
	int		j;
	int		count;

	initialize(&i, &j, &count);
	while (str[i])
	{
		while (str[i] == sep && str[i] != 0)
			i++;
		while (str[i] != sep && str[i] != 0)
		{
			i++;
			j++;
		}
		if (j > 0)
		{
			res[count] = malloc(j + 1);
			if (!res[count])
				ft_frees(res, count);
			res[count][j] = 0;
		}
		j = 0;
		count++;
	}
	return (res);
}

char	**ft_split(char *str, char sep)
{
	char	**res;
	int		i;
	int		j;
	int		count;

	initialize(&i, &j, &count);
	res = malloc((count_words(str, sep) + 1) * sizeof(char *));
	if (!res)
		return (0);
	res[count_words(str, sep)] = 0;
	res = ft_mal(res, str, sep);
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		while (str[i] && str[i] != sep)
		{
			res[count][j] = str[i];
			i++;
			j++;
		}
		j = 0;
		count++;
	}
	return (res);
}

/*
int main()
{
	int i = 0;
	char **res = ft_split("aaaa");
	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
		printf("IIIIIIIIIII %i\n", i);
	}
	ft_free(res, 1);
	//printf("%s\n", res[0]);
	res = ft_split(" aaaaa aaaa aaa");
	i = 0;
	//printf("%s\n", res[0]);
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
		printf("IIIIIIIIIII %i\n", i);
	}
	ft_free(res, 4);
	res = ft_split(" a aa a    ");
	//printf("%s\n", res[0]);
	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
		printf("IIIIIIIIIII %i\n", i);
	}
	ft_free(res, 4);
}*/
