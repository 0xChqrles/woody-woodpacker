/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:22 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:47:32 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ht(t_pline *pline, char c)
{
	if (pline->dotb && pline->dotv > pline->size)
		pline->len -= pline->dotv - pline->size;
	if (pline->dotb)
		pline->zero = false;
	if (pline->ht)
	{
		pline->len--;
		if (c != 'o' && c != 'O')
			pline->len--;
		if (!pline->zero)
			ft_print_width(pline, c);
		pline->count += c == 'o' || c == 'O' ? 1 : 2;
		ft_putchar('0');
		if (c != 'o' && c != 'O')
			ft_putchar(c == 'X' ? 'X' : 'x');
		ft_print_prec(pline, c);
		if (pline->zero)
			ft_print_width(pline, c);
	}
}

void	ft_print_plus(t_pline *pline, char c)
{
	if (!pline->csign && !pline->neg && pline->plus
	&& (c == 'd' || c == 'D' || c == 'f' || c == 'F' || c == 'i'))
	{
		ft_putchar('+');
		pline->count++;
		pline->csign = true;
	}
	else
		ft_check_sign(pline, c);
}

void	ft_print_width(t_pline *pline, char c)
{
	if (pline->nbase)
		pline->len++;
	if (pline->zero && !pline->nbase)
		ft_print_plus(pline, c);
	if (c == 'p' && !pline->nbase && pline->zero)
		ft_putstr("0x");
	while (!pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(pline->zero && !pline->nbase ? '0' : ' ');
	if (!pline->zero || pline->nbase)
		ft_print_plus(pline, c);
	if (c == 'p' && (pline->nbase || !pline->zero))
		ft_putstr("0x");
}

void	ft_print_prec(t_pline *pline, char c)
{
	int	tmp;

	if (c == 'd' || c == 'D' || c == 'x' || c == 'X' || c == 'u'
	|| c == 'U' || c == 'o' || c == 'O' || c == 'i' || c == 'p')
	{
		tmp = pline->neg ? pline->dotv - pline->size + 1
		: pline->dotv - pline->size;
		if ((c == 'o' || c == 'O') && pline->ht)
			tmp--;
		if (tmp > 0)
			ft_print_plus(pline, c);
		while (tmp-- > 0 && ++pline->count)
			ft_putchar('0');
	}
}

void	ft_print_space(t_pline *pline, const char *msg)
{
	if (msg[pline->iflag] != '%' && msg[pline->iflag] != 'u'
	&& msg[pline->iflag] != 's' && msg[pline->iflag] != 'S'
	&& msg[pline->iflag] != 'C' && msg[pline->iflag] != 'c'
	&& msg[pline->iflag] != 'X' && msg[pline->iflag] != 'x'
	&& msg[pline->iflag] != 'o' && msg[pline->iflag] != 'O'
	&& msg[pline->iflag] != 'p' && !pline->bspace && !pline->neg
	&& !pline->csign && !pline->l && !pline->h && !pline->plus
	&& !pline->dotb && !pline->j && !pline->z && !pline->hh && !pline->ll
	&& pline->spaces > 0 && ++pline->count)
		ft_putchar(' ');
}
