/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:31:52 by amazurok          #+#    #+#             */
/*   Updated: 2018/05/29 16:07:37 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

t_oper	*ft_new_oper(void)
{
	t_oper	*new;

	new = (t_oper *)malloc(sizeof(t_oper));
	new->arg1 = NULL;
	new->arg2 = NULL;
	new->arg3 = NULL;
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_label	*ft_new_label(void)
{
	t_label *new;

	new = (t_label *)malloc(sizeof(t_label));
	new->oper = NULL;
	new->name = NULL;
	new->len = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
