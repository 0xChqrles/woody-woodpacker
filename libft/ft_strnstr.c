/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:00 by clanier           #+#    #+#             */
/*   Updated: 2016/11/05 16:34:01 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t n)
{
	size_t		len;
	size_t		i;
	size_t		pos;

	len = ft_strlen(needle);
	i = 0;
	pos = 0;
	if (len == 0)
		return (haystack);
	while (haystack[i] && i < (n - len + 1) && len <= n)
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
