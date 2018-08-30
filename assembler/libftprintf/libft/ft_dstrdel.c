/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deldstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:16:52 by amazurok          #+#    #+#             */
/*   Updated: 2018/05/06 09:56:15 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dstrdel(char ***dstr)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = *dstr;
	if (!tmp)
		return ;
	while (tmp[i])
		ft_strdel(&tmp[i++]);
	free(*dstr);
	*dstr = NULL;
}
