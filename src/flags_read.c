/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:42:40 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/12 15:29:45 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	create_fla(t_fla *flag)
{
	flag->v = 0;
	flag->n = -1;
	flag->dump = -1;
}

int		ft_arr_dig(char *arr, t_game *game)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		if (!ft_isdigit(arr[i]))
			ft_error("Flag is not valid", game);
		i++;
	}
	return (1);
}

int		flags_read(char **argv, int argc, t_fla *flag, t_game *game)
{
	int i;

	i = 0;
	while (i < argc && argv[i])
	{
		if (!ft_strcmp(argv[i], "-v"))
			flag->v++;
		else if (!ft_strcmp(argv[i], "-n") && argv[i + 1] \
				&& ft_arr_dig(argv[i + 1] + (argv[i + 1][0] == '-'), game))
		{
			flag->n = ft_atoi(argv[++i]);
			return (i + 1);
		}
		else if (!ft_strcmp(argv[i], "-dump") && argv[i + 1] \
				&& ft_arr_dig(argv[i + 1], game))
			flag->dump = ft_atoi(argv[++i]);
		else if (argv[i][0] == '-' && !ft_strstr(argv[i], ".cor"))
			ft_error("There is no such flag", game);
		else
			return (i);
		i++;
	}
	return (i);
}
