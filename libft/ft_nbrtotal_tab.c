/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrtotal_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:06:07 by clanier           #+#    #+#             */
/*   Updated: 2016/11/08 14:55:04 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrtotal_tab(int rows, int lines, int **tab)
{
	int	i;
	int	j;
	int total;

	i = 0;
	j = 0;
	total = 0;
	while (i < lines)
	{
		while (j < rows)
		{
			total += tab[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (total);
}
