/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:03 by clanier           #+#    #+#             */
/*   Updated: 2016/11/06 00:02:36 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	find = c;
	int			i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == find)
		{
			s += i;
			return ((char*)s);
		}
		i--;
	}
	return (NULL);
}
