/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:58:02 by oshvorak          #+#    #+#             */
/*   Updated: 2017/10/30 17:58:03 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	int		k;
	char	*arr;

	i = 0;
	j = 0;
	k = 0;
	if (s && f)
	{
		if ((arr = ft_strnew(ft_strlen(s))))
			while (s[i])
				arr[j++] = f(k++, s[i++]);
		return (arr);
	}
	return (NULL);
}
