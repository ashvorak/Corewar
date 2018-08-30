/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputwstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:33:59 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/04 19:34:07 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putustr_fd(wchar_t *wstr, int fd)
{
	int i;

	i = 0;
	while (wstr && wstr[i])
	{
		if (wstr[i] == 127)
		{
			write(fd, "\0", 1);
			i++;
		}
		else if (wstr[i] < 128)
			write(fd, &wstr[i++], 1);
		else
			ft_putuchar_fd(wstr[i++], fd);
	}
}
