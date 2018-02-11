/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:15 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:36 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_id(t_pline *pline)
{
	pline->count += ft_pnbrlen(pline, pline->id);
	ft_putnbr(pline->id);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_o(t_pline *pline)
{
	int		i;
	int		n;
	double	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = (double)pline->o / pow;
		ft_putchar(n + 48);
		pline->o -= (unsigned int)pow * (unsigned int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_x(t_pline *pline, char c)
{
	int		i;
	int		n;
	double	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = (double)pline->x / pow;
		ft_print_hex(n, c);
		pline->x -= (unsigned int)pow * (unsigned int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_p(t_pline *pline)
{
	pline->lx = (unsigned long int)pline->p;
	pline->count += 2;
	if (!pline->lx)
	{
		if ((!pline->dotb || (pline->dotb && pline->dotv)) && ++pline->count)
			ft_putchar('0');
		while (pline->minus && pline->len-- > 0 && ++pline->count)
			ft_putchar(' ');
		return (++pline->i);
	}
	return (ft_flag_lx(pline, 'x'));
}

int		ft_flag_u(t_pline *pline)
{
	if (!pline->nbase)
	{
		pline->count += ft_u_nbrlen(pline, pline->u);
		ft_uputnbr(pline->u);
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
