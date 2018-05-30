/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:50:46 by oshvorak          #+#    #+#             */
/*   Updated: 2017/11/04 19:05:12 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			wnum(char const *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (ft_isprint(s[i]) && s[i] != c)
		{
			num++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (num);
}

static	int			wlen(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static	char		**free_arr(char **arr)
{
	while (*arr)
		free(*arr++);
	arr = NULL;
	return (arr);
}

char				**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**arr;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * (wnum(s, c) + 1))))
		return (NULL);
	while (s[i])
		if (s[i] != c && s[i])
		{
			len = wlen(s + i, c);
			if (!(arr[j++] = ft_strsub(s, i, len)))
				return (free_arr(arr));
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	arr[j] = NULL;
	return (arr);
}
