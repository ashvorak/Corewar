/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 22:18:26 by oshvorak          #+#    #+#             */
/*   Updated: 2017/08/29 12:34:29 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	if (needle[0] == '\0')
		return (char*)(haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		q = 0;
		if (haystack[i] == needle[j])
		{
			q = i;
			while (needle[j] != '\0' && haystack[q] == needle[j])
			{
				if (needle[j + 1] == '\0' && needle[j] == haystack[q])
					return (char*)(haystack + i);
				q++;
				j++;
			}
		}
		i++;
	}
	return (0);
}
