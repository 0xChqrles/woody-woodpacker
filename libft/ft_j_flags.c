/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_j_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:27:38 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:09 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_ju(t_pline *pline)
{
	uintmax_t	pow;
	int			n;
	int			i;

	i = ft_uj_nbrlen(pline, pline->ju);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->ju / pow;
		ft_putchar(n + 48);
		pline->ju -= pow * (uintmax_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_jid(t_pline *pline)
{
	intmax_t	pow;
	int			n;
	int			i;

	ft_long_overflow(pline, 'j');
	if (pline->jid < 0)
	{
		pline->count++;
		pline->jid = -pline->jid;
		ft_putchar('-');
	}
	i = ft_j_nbrlen(pline, pline->jid);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->jid / pow;
		ft_putchar(n + 48);
		pline->jid -= pow * (intmax_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_jo(t_pline *pline)
{
	int			i;
	int			n;
	uintmax_t	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->jo / pow;
		ft_putchar(n + 48);
		pline->jo -= (uintmax_t)pow * (uintmax_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_jx(t_pline *pline, char c)
{
	int			i;
	int			n;
	uintmax_t	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->jx / pow;
		ft_print_hex(n, c);
		pline->jx -= (uintmax_t)pow * (uintmax_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
