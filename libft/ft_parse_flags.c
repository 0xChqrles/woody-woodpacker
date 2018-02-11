/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:04 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:37 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_len_modif(t_pline *pline, char *msg)
{
	if (msg[pline->iflag] == 'l' && pline->l)
		pline->ll = true;
	else if (msg[pline->iflag] == 'l')
		pline->l = true;
	else if (msg[pline->iflag] == 'h' && pline->h)
		pline->hh = true;
	else if (msg[pline->iflag] == 'h')
		pline->h = true;
	else if (msg[pline->iflag] == 'j')
		pline->j = true;
	else if (msg[pline->iflag] == 'z')
		pline->z = true;
	else
		return (0);
	pline->iflag++;
	return (1);
}

int		ft_basic_flags(t_pline *pline, char *msg)
{
	if (msg[pline->iflag] == '.')
	{
		pline->dotv = 0;
		pline->dotb = true;
		pline->dot = true;
	}
	else if (msg[pline->iflag] == '0')
		pline->zero = true;
	else if (msg[pline->iflag] == '+')
		pline->plus = true;
	else if (msg[pline->iflag] == '-')
		pline->minus = true;
	else if (msg[pline->iflag] == '#')
		pline->ht = true;
	else if (msg[pline->iflag] == '0' && !pline->dot)
		pline->zero = true;
	else
		return (0);
	pline->iflag++;
	return (1);
}

int		ft_star_flags(t_pline *pline, char *msg)
{
	if (msg[pline->iflag] == '*' && pline->dot)
	{
		pline->dot = false;
		pline->star = true;
		pline->dstar = true;
		pline->dvstar = va_arg(pline->ap, int);
	}
	else if (msg[pline->iflag] == '*')
	{
		pline->star = true;
		pline->lstar = true;
		pline->lvstar = va_arg(pline->ap, int);
	}
	else
		return (0);
	pline->iflag++;
	return (1);
}

int		ft_width_modif(t_pline *pline, char *msg)
{
	if (msg[pline->iflag] != ' ' && !pline->dot)
	{
		pline->lstar = false;
		pline->len = ft_atoi(msg + pline->iflag);
		pline->iflag += ft_pnbrlen(pline, pline->len) - 1;
		pline->dlen = pline->len;
	}
	else if (msg[pline->iflag] != ' ' && pline->dot)
	{
		pline->dstar = false;
		pline->dotv = ft_atoi(msg + pline->iflag);
		pline->dot = false;
		pline->iflag += ft_pnbrlen(pline, pline->dotv) - 1;
		pline->dlen = pline->dotv;
	}
	else
		return (0);
	pline->iflag++;
	return (1);
}

int		ft_check_flags(t_pline *pline, char *msg)
{
	if (msg[pline->iflag] == ' ' || msg[pline->iflag] == 'l'
			|| msg[pline->iflag] == 'h' || msg[pline->iflag] == 'j'
			|| msg[pline->iflag] == 'z' || msg[pline->iflag] == '+'
			|| msg[pline->iflag] == 'j' || msg[pline->iflag] == 'L')
		pline->spaces++;
	if (ft_len_modif(pline, msg))
		return (1);
	if (ft_basic_flags(pline, msg))
		return (1);
	if (ft_star_flags(pline, msg))
		return (1);
	if ((msg[pline->iflag] > '9' || msg[pline->iflag] < '0')
			&& msg[pline->iflag] != ' ')
		return (0);
	if (ft_width_modif(pline, msg))
		return (1);
	pline->iflag++;
	return (1);
}
