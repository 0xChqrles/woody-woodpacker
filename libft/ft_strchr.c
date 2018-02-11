/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:32:59 by clanier           #+#    #+#             */
/*   Updated: 2017/02/02 18:31:03 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	find = c;

	if (!s)
		return (NULL);
	while (*s != find)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}
