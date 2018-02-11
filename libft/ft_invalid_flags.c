/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invalid_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:53:20 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:01 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_invalid_flag(t_pline *pline, char c)
{
	if (pline->dlen > 0)
	{
		pline->count++;
		if (pline->minus)
			ft_putchar(c);
		while (pline->dlen-- > 0 && ++pline->count)
			ft_putchar(pline->zero && !pline->minus ? '0' : ' ');
		if (!pline->minus)
			ft_putchar(c);
		pline->i += pline->iflag + 1;
	}
	else if (pline->spaces)
		pline->i += pline->spaces;
}
