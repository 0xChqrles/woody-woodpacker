/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_z_lens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:37 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:59 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_z_nbrlen(t_pline *pline, size_t n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

int		ft_z_octlen(t_pline *pline, size_t n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 0;
	if (n == 0)
	{
		if (!pline->dotb)
			pline->ht = false;
		return (1);
	}
	while (n > 0)
	{
		n /= 8;
		i++;
	}
	return (i);
}

int		ft_z_hexlen(t_pline *pline, size_t n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 0;
	if (n == 0)
	{
		pline->ht = false;
		return (1);
	}
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
