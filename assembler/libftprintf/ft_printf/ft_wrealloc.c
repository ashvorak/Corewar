/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:40:02 by amazurok          #+#    #+#             */
/*   Updated: 2018/05/16 11:51:00 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*ft_myrealloc(wchar_t *wtr, size_t size)
{
	wchar_t *nwres;

	nwres = (wchar_t*)malloc(sizeof(wchar_t) * (size + 1));
	nwres = ft_wtrzero(nwres, size + 1);
	if (wtr)
	{
		nwres = ft_wtrcpy(nwres, wtr);
		ft_wstrdel(&wtr);
	}
	return (nwres);
}
