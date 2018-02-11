/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:55 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 07:30:29 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	ft_strstart(const char *s)
{
	int start;

	start = 0;
	while (s[start] == '\t' || s[start] == ' ' || s[start] == '\n')
		start++;
	return (start);
}

static int	ft_strend(const char *s, int start)
{
	int end;

	end = ft_strlen(s) - 1;
	if (s[start] != '\0')
		while (s[end] == '\t' || s[end] == ' ' || s[end] == '\n')
			end--;
	return (end);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	if (s)
	{
		i = 0;
		start = ft_strstart(s);
		end = ft_strend(s, start);
		if ((str = (char *)malloc(sizeof(char) * (end - start + 1))) == NULL)
			return (NULL);
		while (start <= end)
		{
			str[i] = s[start];
			start++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
