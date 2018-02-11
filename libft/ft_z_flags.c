/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_z_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:32 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:56 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_zu(t_pline *pline)
{
	size_t	pow;
	int		n;
	int		i;

	i = ft_z_nbrlen(pline, pline->zu);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->zu / pow;
		ft_putchar(n + 48);
		pline->zu -= pow * (size_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_zid(t_pline *pline)
{
	size_t	pow;
	int		n;
	int		i;

	ft_long_overflow(pline, 'z');
	i = ft_z_nbrlen(pline, pline->zid);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->zid / pow;
		ft_putchar(n + 48);
		pline->zid -= pow * (size_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_zo(t_pline *pline)
{
	int		i;
	int		n;
	size_t	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->zo / pow;
		ft_putchar(n + 48);
		pline->zo -= (size_t)pow * (size_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_zx(t_pline *pline, char c)
{
	int		i;
	int		n;
	size_t	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->zx / pow;
		ft_print_hex(n, c);
		pline->zx -= (size_t)pow * (size_t)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
