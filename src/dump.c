/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 09:29:19 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/13 09:29:19 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	dump_memory(t_game *game)
{
	unsigned int		i;
	char				*tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			
			ft_printf("\n0x%x : ", i);
		}
		tmp = ft_itoa_base(game->area[i].value, 16);
		if (ft_strlen(tmp) == 1)
			ft_printf("0");
		ft_printf("%s ", tmp);
		ft_strdel(&tmp);
		i++;
	}
	printf("\n");
	exit (0);
}