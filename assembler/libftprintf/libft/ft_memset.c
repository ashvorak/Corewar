/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:57:17 by amazurok          #+#    #+#             */
/*   Updated: 2017/10/29 18:56:22 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *a;
	unsigned long i;

	a = (unsigned char*)b;
	i = 0;
	while (i < len)
		a[i++] = (unsigned char)c;
	return (b);
}
