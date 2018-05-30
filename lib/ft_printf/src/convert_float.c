/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:56:36 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/05 18:21:41 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static double	fix_accuracy(double v_double, t_spec *spec)
{
	int		i;
	ssize_t tmp_i;
	double	tmp_d;
	double	acc;

	i = 0;
	acc = 1;
	tmp_d = v_double;
	tmp_i = (ssize_t)tmp_d;
	tmp_d -= (double)tmp_i;
	while (i <= spec->accuracy)
	{
		acc /= 10;
		tmp_d *= 10;
		tmp_i = (ssize_t)tmp_d;
		tmp_d -= (ssize_t)tmp_d;
		i++;
	}
	tmp_i = (tmp_i < 0) ? -tmp_i : tmp_i;
	if (tmp_i >= 5)
		acc *= 10;
	return (acc);
}

static char		*create_v(double v_double, ssize_t v_int, char *v, int accuracy)
{
	int		i;
	char	*buf;

	i = 0;
	buf = NULL;
	while (i < accuracy)
	{
		v_double *= 10;
		v_int = (ssize_t)v_double;
		v_double -= (ssize_t)v_double;
		v = ft_realloc(v, ft_strlen(v));
		buf = ft_itoa(v_int);
		v = ft_strcat(v, buf);
		(buf) ? free(buf) : 0;
		i++;
	}
	return (v);
}

static char		*fix_v(char *v, double v_double)
{
	if (v_double < 0.0 && v_double > -1.0)
	{
		v = ft_realloc(v, ft_strlen(v));
		v[0] = '-';
		v[1] = '0';
	}
	return (v);
}

char			*convert_float(double v_double, t_spec *spec)
{
	double	acc;
	ssize_t	v_int;
	char	*v;

	(spec->accuracy == UNDEFINED) ? spec->accuracy = 6 : 0;
	acc = fix_accuracy(v_double, spec);
	if (spec->accuracy == 0)
		v_double += (v_double > 0) ? acc : -acc;
	v_int = (ssize_t)v_double;
	v = convert_int(v_int);
	v = fix_v(v, v_double);
	if (spec->accuracy != 0)
	{
		v = ft_realloc(v, ft_strlen(v));
		v = ft_strcat(v, ".");
	}
	v_double = (v_double < 0) ? -v_double : v_double;
	v_int = (v_int < 0) ? -v_int : v_int;
	v_double -= (double)v_int;
	if (spec->accuracy != 0)
		v_double += (v_double > 0) ? acc : -acc;
	v = create_v(v_double, v_int, v, spec->accuracy);
	return (v);
}
