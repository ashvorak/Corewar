/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:44:42 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/30 16:50:19 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static unsigned int	get_magic(char *buf)
{
	char *tmp;

	tmp = ft_strsub(buf, 0, 9);
	if (ft_strcmp(tmp, "00ea 83f3"))
		ft_error();
	return (COREWAR_EXEC_MAGIC);
}

static void			get_prog_name(t_player *player, char *buf)
{
 	unsigned int	i;
	unsigned int	j;
	char			*tmp1;
	char			*tmp2;

	i = 0;
	j = 0;
	tmp1 = ft_strsub(buf, 10, 319);
	while (i < 128)
	{
		tmp2 = ft_strsub(tmp1, j, 2);
		player->prog_name[i++] = ft_atoi_base(tmp2, 16);
		j += 2;
		j += (tmp1[j] == ' ' || tmp1[j] == '\n') ? 1 : 0;
		ft_strdel(&tmp2);
	}
	player->prog_name[i] = '\0';
	ft_strdel(&tmp1);
}

static unsigned int	get_prog_size(char *buf)
{
	char *tmp;
	char *tmp1;
	char *tmp2;
	unsigned int	ret;

	tmp1 = ft_strsub(buf, 340, 4);
	tmp2 = ft_strsub(buf, 345, 4);
	tmp = ft_strjoin(tmp1, tmp2);
	ret = (unsigned int)ft_atoi_base(tmp, 16);
	return (ret);
}

static void			get_comment(t_player *player, char *buf)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp1;
	char			*tmp2;

	i = 0;
	j = 0;
	tmp1 = ft_strsub(buf, 350, 5119);
	while (i < 2048)
	{
		tmp2 = ft_strsub(tmp1, j, 2);
		player->comment[i++] = ft_atoi_base(tmp2, 16);
		j += 2;
		j += (tmp1[j] == ' ' || tmp1[j] == '\n') ? 1 : 0;
		ft_strdel(&tmp2);
	}
	player->comment[i] = '\0';
	ft_strdel(&tmp1);
}

static void			get_opcode(t_player *player, char *buf)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(player->opcode = (char**)malloc(sizeof(char*) * (player->prog_size + 1))))
		exit(1);
	while (i < player->prog_size)
	{
		if (!(player->opcode[i] = (char*)malloc(sizeof(char))))
			exit(1);
		tmp = ft_strsub(buf, j, 2);
		player->opcode[i++] = tmp;
		j += 2;
		j += (buf[j] == ' ' || buf[j] == '\n') ? 1 : 0;
	}
	player->opcode[i] = NULL;
}

static	char *read_buf(int fd)
{
	int 	i;
	char	*line;
	char	*tmp;
	char	*buf;

	i = 0;
	buf = NULL;
	while (i < 137 && get_next_line(fd, &line))
	{
		ft_strlen(line) != 39 ? ft_error() : 0;
		if (buf)
		{
			tmp = ft_strdup(buf);
			ft_strdel(&buf);
			buf = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
		}
		else
			buf = ft_strdup(line);
		buf = ft_strjoin(buf, "\n");
		ft_strdel(&line);
		i++;
	}
	(i != 137) ? ft_error() : 0;
	return (buf);
}

static	char *read_opcode(int fd)
{
	char	*line;
	char	*tmp;
	char	*buf;

	buf = NULL;
	while (get_next_line(fd, &line))
	{
		if (buf)
		{
			tmp = ft_strdup(buf);
			ft_strdel(&buf);
			buf = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
		}
		else
			buf = ft_strdup(line);
		buf = ft_strjoin(buf, "\n");
		ft_strdel(&line);
	}
	return (buf);
}
//валидация для опкода
t_player	read_player(char *file)
{
	int			fd;
	char		*buf;
	t_player	player;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error();
	buf = read_buf(fd);
	player.magic = get_magic(buf);
	get_prog_name(&player, buf);
	player.prog_size = get_prog_size(buf);
	get_comment(&player, buf);
	buf = read_opcode(fd);
	get_opcode(&player, buf);
	close(fd);
	return (player);
}
