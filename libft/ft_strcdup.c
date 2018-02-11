/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:28:05 by clanier           #+#    #+#             */
/*   Updated: 2017/02/02 18:56:37 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strcdup(const char *s, char c)
{
	char	*str;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[size] && s[size] != c)
		size++;
	if (!(str = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
