/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:21:43 by amazurok          #+#    #+#             */
/*   Updated: 2018/05/31 18:21:43 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

t_label		*ft_gotoheadlb(t_label *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

t_oper		*ft_gotoheadop(t_oper *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

int			ft_go2end(char *str, int i)
{
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
