/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:11:55 by oshvorak          #+#    #+#             */
/*   Updated: 2017/12/07 14:05:30 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl_list	*ft_gnl_list_new(int fd)
{
	t_gnl_list *list;

	if (!(list = (t_gnl_list*)malloc(sizeof(t_gnl_list))))
		return (NULL);
	list->fd = fd;
	list->start_i = 0;
	list->buff = NULL;
	list->end_line = 0;
	list->next = NULL;
	return (list);
}

static char			*ft_realloc(char *str, int size)
{
	char *nstr;

	if (!(nstr = ft_strnew(size + 1)))
		return (NULL);
	if (str)
	{
		ft_memcpy(nstr, str, size);
		ft_strdel(&str);
	}
	return (nstr);
}

static char			*ft_rfile(int fd, t_gnl_list *elem, char *str)
{
	int		i;
	int		r;
	int		size;
	char	buf[BUFF_SIZE + 1];

	while (!(elem->end_line) && (r = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		buf[r] = '\0';
		size = (str) ? (int)ft_strlen(str) : 0;
		while (buf[i])
		{
			if (buf[i] == '\n')
			{
				(r - i - 1) ? elem->buff = ft_strsub(buf, i + 1, r - i - 1) : 0;
				elem->end_line = 1;
				(!str) ? str = ft_strnew(0) : 0;
				break ;
			}
			str = ft_realloc(str, size + i);
			str[size + i] = buf[i];
			i++;
		}
	}
	return (str);
}

static char			*ft_rbuf(t_gnl_list *elem, char *line)
{
	int i;

	i = elem->start_i;
	while (elem->buff[i] != '\n' && elem->buff[i])
		i++;
	if (i - elem->start_i || elem->buff[i] != '\0')
		line = ft_strsub(elem->buff, elem->start_i, i - elem->start_i);
	if (!(elem->buff[i]))
	{
		ft_strdel(&(elem->buff));
		elem->start_i = 0;
	}
	else
	{
		elem->start_i = ++i;
		elem->end_line = 1;
	}
	return (line);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl_list	*list;
	t_gnl_list			*head;

	if (fd < 0 || !line || (read(fd, NULL, 0) == -1))
		return (-1);
	if (!(list))
		list = ft_gnl_list_new(fd);
	head = list;
	while (list->fd != fd && list->next)
		list = list->next;
	if (list->fd != fd)
	{
		list->next = ft_gnl_list_new(fd);
		list = list->next;
	}
	*line = NULL;
	(list->buff) ? *line = ft_rbuf(list, *line) : 0;
	(!list->end_line) ? *line = ft_rfile(fd, list, *line) : 0;
	list->end_line = 0;
	list = head;
	if (!*line)
		return (0);
	return (1);
}
