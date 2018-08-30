/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtounicat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:14 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/04 19:39:42 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*ft_wtrcpy(wchar_t *w1, wchar_t *w2)
{
	size_t i;

	i = 0;
	while (w2 && w2[i])
	{
		w1[i] = w2[i];
		i++;
	}
	w1[i] = w2[i];
	return (w1);
}

wchar_t	*ft_wtrcat(wchar_t *wtr, wchar_t *wtr2)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (wtr[i])
		i++;
	while (wtr2 && wtr2[k])
		wtr[i++] = wtr2[k++];
	return (wtr);
}

wchar_t	*ft_mystrncat(wchar_t *wtr, char *str, int n)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (wtr[i])
		i++;
	while (k < n)
		wtr[i++] = str[k++];
	return (wtr);
}

wchar_t	*ft_mystrcat(wchar_t *wtr, char *str)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (wtr[i])
		i++;
	while (str[k])
		wtr[i++] = str[k++];
	return (wtr);
}
