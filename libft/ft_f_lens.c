/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_lens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:12 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:33 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_floatlen(t_pline *pline)
{
	pline->f = va_arg(pline->ap, double);
	if (!pline->dotb)
		pline->dotv = 6;
	if (pline->f < 0)
		pline->neg = true;
	return (ft_pnbrlen(pline, (int)pline->f) + pline->dotv + 1);
}
