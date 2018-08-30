/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:51:19 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/02 13:48:55 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITE_H
# define FT_WRITE_H

# include "op.h"
# include "read.h"
# include "./libftprintf/libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

typedef struct	s_bin
{
	ssize_t	i;
	ssize_t	size;
	ssize_t	j;
	t_uchar *res;
	ssize_t oldsize;
	ssize_t bytelen;
	ssize_t opr;
	ssize_t progsize;
}				t_bin;

void			ft_add_num(t_bin *bin, t_uint num);
ssize_t			ft_find_len2link(t_label *label, char *arg);
int				ft_write(t_header data, t_label *a, char *filename);
t_bin			*ft_create_bin(t_bin *bin);
void			ft_del_bin(t_bin *bin);
ssize_t			ft_return_oper_ind(char *name);
void			ft_add_basic(t_header data, t_bin *bin);
void			ft_add_opcode(t_bin *bin, t_label *label);
void			ft_find_arg_type(t_label *label, t_bin *bin, t_label *head);
void			ft_add_2_bytenum(ssize_t num, t_bin *bin);
void			ft_add_4_bytenum(ssize_t num, t_bin *bin);
void			ft_print_result(char *filename, t_uchar *res, ssize_t size);

#endif
