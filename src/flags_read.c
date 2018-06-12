/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:42:40 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/12 14:12:10 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	create_fla(t_fla *flag)
{
	flag->v = 0;
	flag->n = 0;
	flag->dump = 0;
}

int flags_read(char **argv, int argc, t_fla *flag)
{
	int i;

	i = 1;
	while (i < argc && argv[i])
	{
		if (!ft_strcmp(argv[i], "-v"))
			flag->v++;
		else if (!ft_strcmp(argv[i], "-n"))
			flag->n++;
		else if (!ft_strcmp(argv[i], "-dump"))
			flag->dump++;
		else if (argv[i][0] == '-' && !ft_strstr(argv[i], ".cor"))
			ft_error("There is no such flag");
		else
			return (i);
		i++;
	}
	return (i);
}
