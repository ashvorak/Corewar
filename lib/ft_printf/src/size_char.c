/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:28:09 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/27 16:23:13 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	size_char(int bits)
{
	if (bits <= 7 || MB_CUR_MAX == 1)
		return (1);
	else if (bits > 7 && bits <= 11)
		return (2);
	else if (bits > 11 && bits <= 16)
		return (3);
	else
		return (4);
}
