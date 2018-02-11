/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_str_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:43:28 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:20 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_call_c_flag(t_pline *pline, char c)
{
	if (c == 'C' || (c == 'c' && pline->l))
		pline->i = ft_flag_lc(pline, va_arg(pline->ap, wint_t));
	else
		pline->i = ft_flag_c(pline, va_arg(pline->ap, int));
}

void	ft_call_s_flag(t_pline *pline, char c)
{
	if (c == 'S' || (c == 's' && pline->l))
		pline->i = ft_flag_ls(pline);
	else if (c == 's')
		pline->i = ft_flag_s(pline);
}
