/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:53:46 by oshvorak          #+#    #+#             */
/*   Updated: 2017/10/30 16:54:21 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *arr;

	if (!(arr = malloc(size + 1)))
		return (NULL);
	ft_memset(arr, '\0', size + 1);
	return (arr);
}
