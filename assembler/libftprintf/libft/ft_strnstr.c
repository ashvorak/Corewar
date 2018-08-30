/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:38:09 by amazurok          #+#    #+#             */
/*   Updated: 2017/10/29 19:04:40 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (!to_find[0])
		return (char*)(str);
	while (str[i])
	{
		j = 0;
		k = 0;
		if (str[i] == to_find[j])
		{
			k = i;
			while (to_find[j] != '\0' && str[k] == to_find[j] && k < len)
			{
				if (to_find[j + 1] == '\0' && str[k] == to_find[j])
					return (char*)(str + i);
				k++;
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
