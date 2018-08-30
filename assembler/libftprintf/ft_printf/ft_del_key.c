/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:37:31 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/19 16:34:14 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_del_key(t_key *key)
{
	free(key->flag);
	free(key->modtype);
	ft_wstrdel(&key->nwres);
	free(key);
}
