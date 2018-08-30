/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:54:18 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 17:05:04 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "op.h"
# include "./libftprintf/libft/libft.h"
# include <errno.h>
# include <stdio.h>

typedef struct	s_oper
{
	char			*name;
	char			*arg1;
	char			*arg2;
	char			*arg3;
	struct s_oper	*next;
	struct s_oper	*prev;
}				t_oper;

typedef struct	s_label
{
	char			*name;
	size_t			len;
	t_oper			*oper;
	struct s_label	*next;
	struct s_label	*prev;
}				t_label;

typedef struct	s_read
{
	int		fd;
	int		a;
	int		nm;
	int		cm;
	char	*file;
	t_label	*label;
}				t_read;

t_label			*ft_new_label(void);
t_oper			*ft_new_oper(void);
void			ft_read(t_read *data, t_header *h);
int				ft_read_key(int c, char **v, t_read *data);
void			ft_read_name_com(t_header *h, t_read *data, char *file);
void			ft_read_code(t_read *data);
void			ft_read_arg_lb(t_read *data, char *trim, int *i);
void			ft_read_label(t_read *data, char *trim, int *i);
int				ft_valid_label(char *lable, int k);
int				ft_valid_opname(char *name);
int				ft_valid_arg(t_read *data, char *arg, t_op op, int arg_n);
t_label			*ft_gotoheadlb(t_label *lst);
t_oper			*ft_gotoheadop(t_oper *lst);
int				ft_go2end(char *str, int i);
char			*ft_del_comm(char *str);
void			ft_del_data(t_read *data);
int				ft_chardospace(char *str, char c);
int				ft_skip_space(char *file, int i);
int				ft_src_name(char *name);
void			ft_error(t_read *data, char *a, void *b, void *c);
int				ft_space(char c);
int				ft_find_lbname(t_label *lst, char *name);

#endif
