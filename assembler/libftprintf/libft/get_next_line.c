/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:32:14 by amazurok          #+#    #+#             */
/*   Updated: 2018/03/23 16:36:35 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_add2list(t_list **list, size_t fd)
{
	t_list *lst;

	lst = *list;
	if (!(*list))
	{
		*list = ft_lstnew("", fd);
		ft_memdel(&lst->content);
		return (*list);
	}
	while (lst->next && lst->content_size != fd)
		lst = lst->next;
	if (lst->content_size == fd)
		return (lst);
	else
	{
		lst->next = ft_lstnew("", fd);
		ft_memdel(&lst->next->content);
		return (lst->next);
	}
}

static char		*ft_newline(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = ft_strnew(ft_strlen(str + i));
	res = ft_strcpy(res, str + i);
	ft_strclr(str);
	ft_strdel(&str);
	return (res);
}

static int		ft_add2line(t_list *lst, char **line)
{
	int i;
	int len;

	i = 0;
	len = (*line) ? ft_strlen(*line) : 0;
	while (lst->content && ((char*)lst->content)[i] && \
		((char*)lst->content)[i] != '\n')
		i++;
	if (i > 0)
	{
		*line = ft_realloc(*line, len + i);
		*line = ft_strncat(*line, lst->content, i);
	}
	if (lst->content && ((char*)lst->content)[i] == '\n')
	{
		if (!*line)
			*line = ft_strnew(0);
		lst->content = ft_newline(lst->content);
		return (1);
	}
	ft_memdel(&lst->content);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	ssize_t			ret;
	char			buf[BUFF_SIZE + 1];
	int				size;
	t_list			*qwe;

	if (fd < 0 || !line || read(fd, buf, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	size = 0;
	*line = NULL;
	qwe = ft_add2list(&head, (size_t)fd);
	if (ft_add2line(qwe, line))
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		size += ret;
		qwe->content = ft_realloc(qwe->content, size);
		qwe->content = ft_strcat(((char*)qwe->content), buf);
		if (ft_add2line(qwe, line))
			return (1);
	}
	if (*line && line[0])
		return (1);
	return (0);
}
