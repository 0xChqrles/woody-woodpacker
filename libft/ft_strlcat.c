/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:33:32 by clanier           #+#    #+#             */
/*   Updated: 2016/11/14 17:05:36 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	char	*s;
	size_t	i;
	int		j;

	j = 0;
	i = ft_strlen(dest);
	if ((s = ft_memchr(dest, '\0', n)) == NULL)
		return (n + ft_strlen(src));
	while (src[j] != '\0' && n - 1 > (i + j))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (ft_strlen(src) + i);
}
