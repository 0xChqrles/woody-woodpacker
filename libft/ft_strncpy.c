/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:33:51 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 07:31:03 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*dst;

	dst = dest;
	while (*src != '\0' && n > 0)
	{
		*dst++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*dst++ = '\0';
		--n;
	}
	return (dest);
}
