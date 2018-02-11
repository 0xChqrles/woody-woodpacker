/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:31:58 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 06:10:00 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char *s;
	unsigned char		*dst;
	unsigned char		chr;

	if (n)
	{
		s = src;
		dst = dest;
		chr = c;
		++n;
		while (--n != 0)
		{
			if ((*dst++ = *s++) == chr)
				return (dst);
		}
	}
	return (0);
}
