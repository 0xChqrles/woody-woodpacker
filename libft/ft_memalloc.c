/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:31:55 by clanier           #+#    #+#             */
/*   Updated: 2016/11/06 01:47:06 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (size == 0)
		return ((void*)0);
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	if (mem == NULL)
		return (NULL);
	mem = ft_memset(mem, 0, size);
	return (mem);
}
