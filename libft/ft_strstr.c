/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:24 by clanier           #+#    #+#             */
/*   Updated: 2016/11/05 16:34:49 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int		len;
	int		i;
	int		pos;

	len = ft_strlen(needle);
	i = 0;
	pos = 0;
	if (len == 0)
		return (haystack);
	while (haystack[i])
	{
		while (needle[pos] == haystack[i + pos])
		{
			if (pos == len - 1)
				return ((char *)haystack + i);
			pos++;
		}
		pos = 0;
		i++;
	}
	return (0);
}
