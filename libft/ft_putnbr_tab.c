/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:48:34 by clanier           #+#    #+#             */
/*   Updated: 2016/11/08 10:45:44 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_tab(int rows, int lines, int **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i != lines)
	{
		while (j != rows)
		{
			ft_putnbr(tab[i][j]);
			j++;
		}
		j = 0;
		ft_putchar('\n');
		i++;
	}
}
