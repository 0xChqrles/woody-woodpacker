/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:09 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:30 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_round_f(t_pline *pline)
{
	double	n;
	long	tmp;

	n = pline->f;
	n *= ft_pow(10, pline->dotv);
	tmp = (long)n;
	n -= (double)tmp;
	if (n > 0.5f)
		pline->f += ft_pow(10, -pline->dotv);
}

void	ft_f_putnbr(t_pline *pline)
{
	intmax_t	f;
	bool		minus;

	f = pline->f;
	minus = pline->minus;
	pline->minus = false;
	pline->jid = f;
	ft_flag_jid(pline);
	pline->minus = minus;
}

int		ft_flag_f(t_pline *pline)
{
	double	n;

	if (pline->f < 0)
	{
		ft_putchar('-');
		pline->count++;
		pline->f = -pline->f;
	}
	pline->count += pline->dotv + 1;
	ft_f_putnbr(pline);
	ft_putchar('.');
	n = pline->f;
	pline->f -= (intmax_t)n;
	ft_round_f(pline);
	while (pline->dotv-- > 0)
	{
		pline->f *= 10.0f;
		ft_putchar((int)pline->f + 48);
		n = (long)pline->f;
		pline->f -= (double)n;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (pline->i);
}
