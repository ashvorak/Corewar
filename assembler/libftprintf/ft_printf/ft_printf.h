/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:24:19 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/19 16:32:34 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"
# include <stddef.h>

typedef unsigned short int		t_usi;
typedef unsigned long int		t_uli;
typedef long long int			t_lli;
typedef unsigned long long int	t_ulli;
typedef uintmax_t				t_uinmax;

typedef struct	s_res
{
	int			size;
	int			i;
	int			fd;
}				t_res;

typedef struct	s_modtype
{
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
	int			lll;
	int			t;
}				t_modtype;

typedef struct	s_flag
{
	int			hash;
	int			zero;
	int			minus;
	int			plus;
	int			space;
}				t_flag;

typedef struct	s_key
{
	t_flag		*flag;
	int			width;
	int			precision;
	t_modtype	*modtype;
	char		sym;
	char		*res;
	int			lenr;
	char		r;
	wchar_t		wr;
	wchar_t		*wres;
	wchar_t		*nwres;
}				t_key;

t_key			*ft_new_key(void);
int				ft_check_key(t_key *key, const char *format, va_list args);
int				ft_print_res(t_key *key, va_list args, t_res *tres);
int				ft_printf(const char *format, ...);
char			*ft_size2a_base(size_t value, int base);
char			*ft_ssize2a_base(ssize_t value, int base);
void			ft_process_args(t_key *key, va_list args, t_res *tres);
char			*ft_struper(char *str);
int				ft_print_char(t_key *key);
int				ft_print_str(t_key *key);
char			*ft_addchar(char *str, char c, int k, int s);
int				ft_print_dig(t_key *key);
int				ft_size(t_key *key, int p, int w);
int				ft_width(t_key *key, int p);
int				ft_precision(t_key *key);
int				ft_print_unic(t_key *key);
int				ft_print_uchar(t_key *key, unsigned int octet);
int				ft_putuchar_fd(unsigned int octet, int fd);
wchar_t			*ft_mystrcat(wchar_t *wtr, char *str);
wchar_t			*ft_myrealloc(wchar_t *wtr, size_t size);
wchar_t			*ft_wtrcat(wchar_t *wtr, wchar_t *wtr2);
void			ft_putustr_fd(wchar_t *wstr, int fd);
wchar_t			*ft_wtrcpy(wchar_t *w1, wchar_t *w2);
wchar_t			*ft_mystrncat(wchar_t *wtr, char *str, int n);
void			ft_wstrdel(wchar_t **wstr);
int				ft_mod_u(wchar_t c);
t_res			*ft_new_tres(void);
wchar_t			*ft_wtrzero(wchar_t *w1, int n);
void			ft_del_key(t_key *key);
wchar_t			*ft_nonpercent(const char **format, wchar_t *wres, \
					const char *frm, t_res *tres);
int				ft_wstrlen(wchar_t *wstr);
void			ft_float2str(t_key *key, va_list args);
void			ft_setn(int *p, t_res *tres);
#endif
