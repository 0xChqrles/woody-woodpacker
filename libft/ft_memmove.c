/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:32:15 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 09:38:56 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*dst;

	s = src;
	dst = dest;
	if (!n)
		return (dest);
	if (dest <= src)
		return (ft_memcpy(dst, src, n));
	s += n;
	dst += n;
	while (n--)
		*--dst = *--s;
	return (dest);
}
