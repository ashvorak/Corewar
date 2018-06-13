/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:20:23 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/04 16:23:45 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static char	*is_color(const char *s)
{
	if (!ft_strcmp(s, "{black}"))
		return (BLACK);
	if (!ft_strcmp(s, "{red}"))
		return (RED);
	if (!ft_strcmp(s, "{green}"))
		return (GREEN);
	if (!ft_strcmp(s, "{yellow}"))
		return (YELLOW);
	if (!ft_strcmp(s, "{blue}"))
		return (BLUE);
	if (!ft_strcmp(s, "{purple}"))
		return (PURPLE);
	if (!ft_strcmp(s, "{seawave}"))
		return (SEAWAVE);
	if (!ft_strcmp(s, "{white}"))
		return (WHITE);
	return (NULL);
}

static char	*is_background(const char *s)
{
	if (!ft_strcmp(s, "{fblack}"))
		return (FBLACK);
	if (!ft_strcmp(s, "{fred}"))
		return (FRED);
	if (!ft_strcmp(s, "{fgreen}"))
		return (FGREEN);
	if (!ft_strcmp(s, "{fyellow}"))
		return (FYELLOW);
	if (!ft_strcmp(s, "{fblue}"))
		return (FBLUE);
	if (!ft_strcmp(s, "{fpurple}"))
		return (FPURPLE);
	if (!ft_strcmp(s, "{fseawave}"))
		return (FSEAWAVE);
	if (!ft_strcmp(s, "{fwhite}"))
		return (FWHITE);
	return (NULL);
}

static char	*is_font(const char *s)
{
	if (!ft_strcmp(s, "{bolid}"))
		return (BOLID);
	if (!ft_strcmp(s, "{sbright}"))
		return (SBRIGHT);
	if (!ft_strcmp(s, "{underl}"))
		return (UNDERL);
	if (!ft_strcmp(s, "{flash}"))
		return (FLASH);
	if (!ft_strcmp(s, "{revers}"))
		return (REVERS);
	return (NULL);
}

int			make_colors(const char *s, int fd)
{
	char *str;

	if ((str = is_color(s)))
	{
		write(fd, str, ft_strlen(str));
		return (1);
	}
	if ((str = is_background(s)))
	{
		write(fd, str, ft_strlen(str));
		return (1);
	}
	if ((str = is_font(s)))
	{
		write(fd, str, ft_strlen(str));
		return (1);
	}
	if (!ft_strcmp(s, "{eoc}"))
	{
		write(fd, RESET, ft_strlen(RESET));
		return (1);
	}
	return (0);
}
