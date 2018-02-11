/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:33:48 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 06:22:33 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n > i)
	{
		if (*s1 != *s2)
			return ((*(unsigned char *)s1 - *(unsigned char *)s2));
		if (*s1 == '\0')
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (0);
}
