/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:41:56 by amazurok          #+#    #+#             */
/*   Updated: 2017/12/12 16:43:12 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *str, size_t size)
{
	char *nstr;

	if (!(nstr = ft_strnew(size)))
		return (NULL);
	if (str)
	{
		ft_strcpy(nstr, str);
		ft_strdel(&str);
	}
	return (nstr);
}
