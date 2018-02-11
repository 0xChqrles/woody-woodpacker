/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:02 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:31 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_llu(t_pline *pline)
{
	unsigned long long int	pow;
	int						n;
	int						i;

	i = ft_ull_nbrlen(pline, pline->llu);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->llu / pow;
		ft_putchar(n + 48);
		pline->llu -= pow * (unsigned long long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_llid(t_pline *pline)
{
	double	pow;
	int		n;
	int		i;

	ft_long_overflow(pline, 'D');
	if (pline->llid < 0)
	{
		pline->count++;
		pline->llid = -pline->llid;
		ft_putchar('-');
	}
	i = ft_ll_nbrlen(pline, pline->llid);
	pline->count += i;
	i--;
	while (i >= 0)
	{
		pow = ft_pow(10, i);
		n = pline->llid / (long long int)pow;
		ft_putchar(n + 48);
		pline->llid -= (long long int)pow * (long long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_llo(t_pline *pline)
{
	int						i;
	int						n;
	unsigned long long int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(8, i);
		n = pline->llo / pow;
		ft_putchar(n + 48);
		pline->llo -= (unsigned long long int)pow * (unsigned long long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_llx(t_pline *pline, char c)
{
	int						i;
	int						n;
	unsigned long long int	pow;

	i = pline->size - 1;
	pline->count += pline->size;
	while (i >= 0)
	{
		pow = ft_pow(16, i);
		n = pline->llx / pow;
		ft_print_hex(n, c);
		pline->llx -= (unsigned long long int)pow * (unsigned long long int)n;
		i--;
	}
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
