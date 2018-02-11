/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hh_lens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:26:48 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:55 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_hh_nbrlen(t_pline *pline, signed char n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 1;
	if (n < 0)
	{
		pline->neg = true;
		i = 2;
		n = -n;
	}
	while (n /= 10)
		i++;
	return (i);
}

int		ft_uhh_octlen(t_pline *pline, unsigned char n)
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

int		ft_uhh_hexlen(t_pline *pline, unsigned char n)
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

int		ft_uhh_nbrlen(t_pline *pline, unsigned char n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 1;
	while (n /= 10)
		i++;
	return (i);
}
