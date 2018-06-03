//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

static int	wlen(size_t value, int base)
{
	int num;

	num = 0;
	while (value)
	{
		value /= base;
		num++;
	}
	return (num);
}

char		*convert(size_t value)
{
	int		i;
	int		base;
	int		buf;
	char	*res;

	if (value == 0)
		return (ft_strdup("00"));
	base = 16;
	i = wlen(value, base);
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	while (value)
	{
		buf = value % base;
		if (buf > 9)
				res[--i] = buf + 87;
		else
			res[--i] = buf + '0';
		value /= base;
	}
	if (ft_strlen(res) < 2)
		res = ft_strjoin("0", res);
	return (res);
}

void    op_add(t_game *game, t_process *process)
{
	unsigned int res;

	res = 0;
	if (!check_codege(process->op_id, ft_atoi_base(game->area[process->PC + 1].value, 16)))
		return ;
	res = ft_atoi_base(game->area[process->PC + 2].value, 16) +
			ft_atoi_base(game->area[process->PC + 3].value, 16);
	ft_strdel(&game->area[process->PC + 4].value);
	game->area[process->PC + 4].value = convert(res);
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}