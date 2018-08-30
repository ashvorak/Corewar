/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:38:25 by amazurok          #+#    #+#             */
/*   Updated: 2017/11/01 13:40:48 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*res;

	i = -1;
	if (s && f)
	{
		if ((res = ft_strnew(ft_strlen(s))))
		{
			while (s[++i])
				res[i] = f(s[i]);
			return (res);
		}
	}
	return (NULL);
}
