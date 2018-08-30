/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:18:13 by amazurok          #+#    #+#             */
/*   Updated: 2018/03/24 11:02:07 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *res;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content_size)
		res->content = NULL;
	else
	{
		if (!(res->content = malloc(sizeof(void) * content_size)))
			return (NULL);
	}
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		ft_memcpy((res->content), content, content_size);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
