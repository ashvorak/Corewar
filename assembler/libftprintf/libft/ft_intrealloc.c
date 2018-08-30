/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:43:43 by amazurok          #+#    #+#             */
/*   Updated: 2018/05/12 12:43:43 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_intrealloc(int *arr, int oldsize)
{
	int *new;
	int i;

	i = 0;
	new = (int*)malloc(sizeof(int) * (oldsize + 1));
	if (arr)
	{
		while (i < oldsize)
		{
			new[i] = arr[i];
			i++;
		}
		free(arr);
	}
	return (new);
}
