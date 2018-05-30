/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:04:16 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/11 14:10:02 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr_int(int **arr, int size)
{
	int i;

	i = 0;
	if (arr)
	{
		while (i < size)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
