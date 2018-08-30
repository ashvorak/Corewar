/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:28:03 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/29 20:40:27 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	is_type(char *types, char type)
{
	while (*types)
	{
		if (*types == type)
			return (TRUE);
		types++;
	}
	return (FALSE);
}
