/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:42:40 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/13 14:14:05 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void			create_fla(t_fla *flag)
{
	flag->v = 0;
	flag->c = 0;
	flag->n = -1;
	flag->l = 0;
	flag->dump = -1;
}

int				ft_arr_dig(char *arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		if (!ft_isdigit(arr[i]))
			ft_usage();
		i++;
	}
	return (1);
}

static t_fla	*flags_read_add(char **argv, int i, t_fla *flag)
{
	if (!ft_strcmp(argv[i], "-c"))
		flag->c++;
	else if (!ft_strcmp(argv[i], "-l"))
		flag->l++;
	return (flag);
}

int				flags_read(char **argv, int argc, t_fla *flag)
{
	int i;

	i = 0;
	while (i < argc && argv[i])
	{
		if (!ft_strcmp(argv[i], "-v"))
			flag->v++;
		else if (!ft_strcmp(argv[i], "-c") || !ft_strcmp(argv[i], "-l"))
			flag = flags_read_add(argv, i, flag);
		else if (!ft_strcmp(argv[i], "-n") && argv[i + 1] \
				&& ft_arr_dig(argv[i + 1] + (argv[i + 1][0] == '-')))
		{
			flag->n = ft_atoi(argv[++i]);
			return (i + 1);
		}
		else if (!ft_strcmp(argv[i], "-dump") && argv[i + 1] \
				&& ft_arr_dig(argv[i + 1]))
			flag->dump = ft_atoi(argv[++i]);
		else if (argv[i][0] == '-' && !ft_strstr(argv[i], ".cor"))
			ft_usage();
		else
			return (i);
		i++;
	}
	return (i);
}
