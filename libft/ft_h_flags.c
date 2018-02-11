/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_h_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:35 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:47 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_hu(t_pline *pline)
{
	int	i;

	i = 0;
	i = ft_uh_nbrlen(pline, pline->hu);
	pline->count += i;
	ft_putnbr((int)pline->hu);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_hid(t_pline *pline)
{
	pline->count += ft_h_nbrlen(pline, pline->hid);
	ft_putnbr((int)pline->hid);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_ho(t_pline *pline)
{
	int					i;
	int					n;
	unsigned short int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->ho / pow;
		ft_putchar(n + 48);
		pline->ho -= (unsigned short int)pow * (unsigned short int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_hx(t_pline *pline, char c)
{
	int					i;
	int					n;
	unsigned short int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->hx / pow;
		ft_print_hex(n, c);
		pline->hx -= (unsigned short int)pow * (unsigned short int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
