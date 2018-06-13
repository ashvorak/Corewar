/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:50:51 by oshvorak          #+#    #+#             */
/*   Updated: 2017/10/30 19:50:52 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(arr = ft_strnew(len)))
		return (NULL);
	while (i < len && s && arr)
		arr[i++] = s[start++];
	return (arr);
}
