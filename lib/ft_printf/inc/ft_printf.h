/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 13:19:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/04 16:20:07 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>
# include "../../libft.h"

# define TRUE 1
# define FALSE 0
# define UNDEFINED -1

# define RESET   "\033[0m"

# define BOLID   "\033[1;1m"
# define SBRIGHT "\033[1;2m"
# define UNDERL  "\033[1;4m"
# define FLASH   "\033[1;5m"
# define REVERS  "\033[1;7m"

# define BLACK   "\033[1;30m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define PURPLE  "\033[1;35m"
# define SEAWAVE "\033[1;36m"
# define WHITE   "\033[1;37m"

# define FBLACK   "\033[1;40m"
# define FRED     "\033[1;41m"
# define FGREEN   "\033[1;42m"
# define FYELLOW  "\033[1;43m"
# define FBLUE    "\033[1;44m"
# define FPURPLE  "\033[1;45m"
# define FSEAWAVE "\033[1;46m"
# define FWHITE   "\033[1;47m"

typedef struct	s_flags
{
	int	minus;
	int	plus;
	int	zero;
	int	space;
	int	hash;
}				t_flags;

typedef enum	e_size
{
	none,
	h,
	hh,
	l,
	ll,
	j,
	z
}				t_size;

typedef struct	s_spec
{
	t_flags	*flags;
	int		width;
	int		accuracy;
	t_size	size;
	char	type;
	int		fd;
}				t_spec;

int				ft_printf(const char *format, ...);
const char		*handle_qualifier(const char *p, t_spec *spec, va_list ap);
char			*convert_int(ssize_t value);
char			*convert_base(size_t value, t_spec *spec);
char			*convert_float(double v_double, t_spec *spec);
int				handle_value(t_spec *spec, va_list ap, int len);
int				handle_char(char c, t_spec *spec);
int				handle_wchar(wchar_t c, t_spec *spec);
int				handle_num(char *value, t_spec *spec);
int				handle_float(char *value, t_spec *spec);
void			handle_n(t_spec *spec, int len, va_list ap);
int				handle_str(char *value, t_spec *spec);
int				handle_wstr(wchar_t *value, t_spec *spec);
void			ft_putwchar(wchar_t value, int bits, int fd);
int				active_bits(wchar_t value);
int				size_char(int bits);
int				is_type(char *types, char type);
int				make_colors(const char *s, int fd);
char			*ft_realloc(char *str, int size);

#endif
