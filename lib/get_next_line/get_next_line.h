/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:26:46 by oshvorak          #+#    #+#             */
/*   Updated: 2017/12/07 14:19:59 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE	8000000

# include <fcntl.h>
# include <stdlib.h>
# include "../libft.h"

typedef	struct			s_gnl_list
{
	int					fd;
	int					start_i;
	char				*buff;
	int					end_line;
	struct s_gnl_list	*next;
}						t_gnl_list;

int						get_next_line(const int fd, char **line);

#endif
