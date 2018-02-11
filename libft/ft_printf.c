/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 17:54:39 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:46 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(int n, char c)
{
	if (c == 'x')
		ft_putchar(n < 10 ? n + 48 : n + 87);
	else
		ft_putchar(n < 10 ? n + 48 : n + 55);
}

void	ft_pline_init(t_pline *pline)
{
	pline->lstar = false;
	pline->dstar = false;
	pline->star = false;
	pline->dlen = 0;
	pline->iflag = 0;
	pline->bspace = false;
	pline->nbase = false;
	pline->ll = false;
	pline->l = false;
	pline->hh = false;
	pline->h = false;
	pline->j = false;
	pline->z = false;
	pline->dot = false;
	pline->dotb = false;
	pline->dotv = 0;
	pline->len = 0;
	pline->spaces = 0;
	pline->minus = false;
	pline->ht = false;
	pline->zero = false;
	pline->plus = false;
	pline->neg = false;
	pline->csign = false;
}

int		ft_iscolor(t_pline *pline, char *msg)
{
	int	i;

	i = 0;
	if (ft_strncmp(msg, "{cyan}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[36m");
	else if (ft_strncmp(msg, "{purp}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[35m");
	else if (ft_strncmp(msg, "{blue}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[34m");
	else if (ft_strncmp(msg, "{red}", 5) == 0 && (pline->count += 5))
		ft_putstr("\033[31m");
	else if (ft_strncmp(msg, "{yell}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[33m");
	else if (ft_strncmp(msg, "{gree}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[32m");
	else if (ft_strncmp(msg, "{bold}", 6) == 0 && ++i && (pline->count += 4))
		ft_putstr("\033[1m");
	else if (ft_strncmp(msg, "{grey}", 6) == 0 && ++i && (pline->count += 5))
		ft_putstr("\033[30m");
	else if (ft_strncmp(msg, "{eoc}", 5) == 0 && (pline->count += 4))
		ft_putstr("\033[0m");
	else
		return (0);
	return (pline->i += i + 4);
}

int		ft_printf(const char *msg, ...)
{
	t_pline		*pline;
	int			count;

	pline = (t_pline*)malloc(sizeof(t_pline));
	va_start(pline->ap, msg);
	pline->i = 0;
	pline->count = 0;
	while (msg[pline->i])
	{
		if (!(pline->color = false) && msg[pline->i] == '{')
			if (ft_iscolor(pline, (char*)msg + pline->i))
				pline->color = true;
		if (msg[pline->i] == '%')
			ft_flags(pline, msg + pline->i + 1);
		else if (!pline->color && ++pline->count)
			ft_putchar(msg[pline->i]);
		pline->i++;
	}
	va_end(pline->ap);
	count = pline->count;
	free(pline);
	return (count);
}
