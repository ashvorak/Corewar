/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:56:28 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/04 16:56:29 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_realloc(char *str, int size)
{
	char *nstr;

	if (!(nstr = ft_strnew(size + 1)))
		return (NULL);
	if (str)
	{
		ft_memcpy(nstr, str, size);
		ft_strdel(&str);
	}
	return (nstr);
}
