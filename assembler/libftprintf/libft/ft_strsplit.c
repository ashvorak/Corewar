/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:50:47 by amazurok          #+#    #+#             */
/*   Updated: 2018/03/31 18:06:15 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_num_word(const char *s, char c)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (s && s[i])
	{
		if (ft_isprint(s[i]) && s[i] != c && (s[i + 1] == c || !s[i + 1]))
			res++;
		i++;
	}
	return (res);
}

int			ft_len_word(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	s = NULL;
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(char*) * (ft_num_word(s, c) + 1))))
		return (NULL);
	while (i < ft_num_word(s, c))
	{
		while (s[j] == c)
			j++;
		if (!(res[i] = ft_strsub(s, j, ft_len_word(s + j, c))))
			return (ft_free(res));
		j += ft_len_word(s + j, c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
