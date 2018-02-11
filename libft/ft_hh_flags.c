/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hh_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:26:59 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:52 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_hhu(t_pline *pline)
{
	int	i;

	i = 0;
	i = ft_uhh_nbrlen(pline, pline->hhu);
	pline->count += i;
	ft_putnbr((int)pline->hhu);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_hhid(t_pline *pline)
{
	pline->count += ft_hh_nbrlen(pline, pline->hhid);
	ft_putnbr((int)pline->hhid);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_hho(t_pline *pline)
{
	int				i;
	int				n;
	unsigned char	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->hho / pow;
		ft_putchar(n + 48);
		pline->hho -= (unsigned char)pow * (unsigned char)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_hhx(t_pline *pline, char c)
{
	int				i;
	int				n;
	unsigned char	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->hhx / pow;
		ft_print_hex(n, c);
		pline->hhx -= (unsigned char)pow * (unsigned char)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
