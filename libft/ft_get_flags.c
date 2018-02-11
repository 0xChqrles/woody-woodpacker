/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:21 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:42 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_get_stars(t_pline *pline, char c)
{
	if (pline->lstar)
	{
		if (pline->lvstar < 0 && (pline->lvstar = -pline->lvstar))
			pline->minus = true;
		pline->len = pline->lvstar;
	}
	if (pline->dstar)
	{
		if (pline->dvstar < 0 && (c == 's' || c == 'S'))
			pline->dvstar = -pline->dvstar;
		pline->dotv = pline->dvstar;
	}
}

void	ft_get_values(t_pline *pline, char c)
{
	if (pline->star)
		ft_get_stars(pline, c);
	if (c == 'U' || c == 'D' || c == 'O')
		pline->l = true;
	if (pline->dotb && !pline->dstar && c != 's'
	&& c != 'S' && c != 'C' && c != 'c' && c != '%')
		pline->zero = false;
	if (c == 'p' && (!pline->ht))
		pline->len -= 2;
	pline->len -= ft_get_size(pline, c);
	if (pline->dotb && pline->size < pline->dotv
	&& (c == 'd' || c == 'D' || c == 'i' || c == 'u'))
		pline->len -= pline->dotv - pline->size;
	if (!pline->neg && pline->plus && (c == 'd'
	|| c == 'D' || c == 'f' || c == 'F' || c == 'i'))
		pline->len--;
	if (pline->dotb && pline->dotv - pline->size >= 0 && pline->neg)
		pline->len--;
	if ((c == 'd' || c == 'i') && pline->len > 0 && !pline->plus
	&& !pline->neg && pline->spaces && ++pline->count)
	{
		ft_putchar(' ');
		pline->bspace = true;
		pline->len--;
	}
}
