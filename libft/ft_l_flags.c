/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:27:23 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:19 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_lu(t_pline *pline)
{
	unsigned long int	pow;
	int					n;
	int					i;

	i = ft_ul_nbrlen(pline, pline->lu);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->lu / pow;
		ft_putchar(n + 48);
		pline->lu -= pow * (unsigned long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_lid(t_pline *pline)
{
	long int	pow;
	int			n;
	int			i;

	ft_long_overflow(pline, 'd');
	if (pline->lid < 0)
	{
		pline->count++;
		pline->lid = -pline->lid;
		ft_putchar('-');
	}
	i = ft_l_nbrlen(pline, pline->lid);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->lid / pow;
		ft_putchar(n + 48);
		pline->lid -= pow * (long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_lo(t_pline *pline)
{
	int					i;
	int					n;
	unsigned long int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->lo / pow;
		ft_putchar(n + 48);
		pline->lo -= (unsigned long int)pow * (unsigned long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_lx(t_pline *pline, char c)
{
	int					i;
	int					n;
	unsigned long int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->lx / pow;
		ft_print_hex(n, c);
		pline->lx -= (unsigned long int)pow * (unsigned long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
