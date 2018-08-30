/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:10:24 by oshvorak          #+#    #+#             */
/*   Updated: 2017/10/27 17:10:35 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*arr1;
	unsigned char	*arr2;

	i = 0;
	arr1 = (unsigned char*)dst;
	arr2 = (unsigned char*)src;
	if (arr2 < arr1)
		while ((int)(--len) >= 0)
			*(arr1 + len) = *(arr2 + len);
	else
		while (i < len)
		{
			*(arr1 + i) = *(arr2 + i);
			i++;
		}
	return (dst);
}
