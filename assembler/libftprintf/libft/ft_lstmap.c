/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:48:11 by amazurok          #+#    #+#             */
/*   Updated: 2017/11/04 17:23:11 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *fin;

	if (lst && f)
	{
		fin = f(lst);
		res = fin;
		while (lst->next)
		{
			res->next = f(lst->next);
			res = res->next;
			lst = lst->next;
		}
		return (fin);
	}
	return (NULL);
}
