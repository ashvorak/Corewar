/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:42:40 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/12 13:47:14 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

t_fla	*create_fla(t_fla *flag)
{
	flag = (t_fla*)malloc(sizeof(t_fla));
	flag->v = 0;
	return (flag);
}

int flags_read(char **argv, int argc, t_fla *flag)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] && argv[i][1] && !argv[i][2])
	{
		if (argv[i][0] == '-' && argv[i][1] == 'v')
			flag->v++;
		else if (argv[i][0] == '-')
			ft_printf("")
		else
			return (i);
		i++;
	}
	return (i);
}
