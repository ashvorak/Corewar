/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:31:35 by amazurok          #+#    #+#             */
/*   Updated: 2017/11/01 13:47:49 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = -1;
	if (s && f)
	{
		if ((res = ft_strnew(ft_strlen(s))))
		{
			while (s[++i])
				res[i] = f(i, s[i]);
		}
		return (res);
	}
	return (NULL);
}
