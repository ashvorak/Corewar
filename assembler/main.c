/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:25:45 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/12 16:51:11 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "ft_write.h"

int		ft_open(char *name)
{
	int fd;

	if ((fd = open(name, O_RDONLY)) > 0)
		return (fd);
	ft_printf("Can't read source file %s\n", name);
	return (-1);
}

int		ft_usage(int argc)
{
	if (argc == 1)
	{
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n    ");
		ft_printf("-a : Instead of creating a .cor file, printing ");
		ft_printf("the code to the standard output\n");
		return (0);
	}
	return (1);
}

int		main(int argc, char *argv[])
{
	t_read		data;
	t_header	h;
	int			i;

	if (!ft_usage(argc))
		return (0);
	i = 1;
	ft_read_key(argc, argv, &data);
	h.magic = COREWAR_EXEC_MAGIC;
	while (i < argc)
	{
		if (!ft_strequ(argv[i], "-a"))
		{
			if ((data.fd = ft_open(argv[i])) > 0)
			{
				ft_read(&data, &h);
				ft_write(h, data.label, argv[i]);
				data.a ? ft_putstr(data.file) : 0;
				ft_del_data(&data);
			}
		}
		i++;
	}
	return (0);
}
