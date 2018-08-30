/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:56:52 by amazurok          #+#    #+#             */
/*   Updated: 2017/10/29 18:55:38 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*a;
	int		i;

	a = (char*)s;
	i = 0;
	while (a[i])
		if (a[i++] == c)
			return (a + i - 1);
	if (a[i] == c)
		return (a + i);
	else
		return (NULL);
}
