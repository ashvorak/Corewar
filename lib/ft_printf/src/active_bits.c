/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:26:58 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/04 15:06:05 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	active_bits(wchar_t value)
{
	int				ret;
	int				size;
	unsigned int	c;

	ret = 0;
	size = 0;
	c = 1;
	while (size < 32)
	{
		size++;
		if ((c & value) != 0)
			ret = size;
		c <<= 1;
	}
	return (ret);
}
