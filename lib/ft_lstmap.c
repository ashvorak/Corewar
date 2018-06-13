/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:25:15 by oshvorak          #+#    #+#             */
/*   Updated: 2017/11/04 17:25:17 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*new_lst;

	if (lst && f)
	{
		head = f(lst);
		new_lst = head;
		while (lst->next)
		{
			new_lst->next = f(lst->next);
			lst = lst->next;
			new_lst = new_lst->next;
		}
		return (head);
	}
	return (NULL);
}
