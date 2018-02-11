/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clrnbr_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:52:47 by clanier           #+#    #+#             */
/*   Updated: 2016/11/08 11:54:50 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	**ft_nbrset_tab(int rows, int lines, int **tab, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lines)
	{
		while (j < rows)
		{
			tab[i][j] = n;
			j++;
		}
		j = 0;
		i++;
	}
	return (tab);
}
