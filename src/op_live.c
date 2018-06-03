//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

void    op_live(t_game *game, t_process *process)
{
	char *tmp;

	process->live++;
	tmp = ft_strjoin(game->area[process->PC + 1].value, game->area[process->PC + 2].value);
	tmp = ft_strjoin(tmp, game->area[process->PC + 3].value);
	tmp = ft_strjoin(tmp, game->area[process->PC + 4].value);
	if (ft_atoi_base(tmp, 16) > 0 && ft_atoi_base(tmp, 16) < 5 && game->players[ft_atoi_base(tmp, 16) - 1].color)
		game->players[ft_atoi_base(tmp, 16) - 1].live = 1;
	ft_strdel(&tmp);
}