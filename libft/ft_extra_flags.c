/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:24:07 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:25 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_percent(t_pline *pline)
{
	pline->count++;
	ft_putchar('%');
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
