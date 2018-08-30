/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:57:55 by amazurok          #+#    #+#             */
/*   Updated: 2018/03/23 10:53:58 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int k;

	i = 0;
	if (!to_find[0])
		return (char*)(str);
	while (str && str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			k = i;
			while (to_find[j] != '\0' && str[k] == to_find[j])
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
