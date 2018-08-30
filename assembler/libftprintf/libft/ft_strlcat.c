/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:56:46 by amazurok          #+#    #+#             */
/*   Updated: 2017/11/03 13:03:50 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t dstsize)
{
	size_t	l;

	l = ft_strlen(s1);
	if (dstsize > l)
		ft_strncat(s1, s2, (dstsize - l - 1));
	if (dstsize < l)
		return (dstsize + ft_strlen(s2));
	else
		return (l + ft_strlen(s2));
}
