/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:23:28 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:02 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_type(t_pline *pline, const char *msg)
{
	while (msg[pline->iflag] != 'f' && msg[pline->iflag] != 'd'
	&& msg[pline->iflag] != 'i' && msg[pline->iflag] != 's'
	&& msg[pline->iflag] != 'c' && msg[pline->iflag] != '%'
	&& msg[pline->iflag] != 'd' && msg[pline->iflag] != 'f'
	&& msg[pline->iflag] != 'x' && msg[pline->iflag] != 'X'
	&& msg[pline->iflag] != 'o' && msg[pline->iflag] != 'u'
	&& msg[pline->iflag] != 'U' && msg[pline->iflag] != 'D'
	&& msg[pline->iflag] != 'O' && msg[pline->iflag] != 'F'
	&& msg[pline->iflag] != 'p' && msg[pline->iflag] != 'S'
	&& msg[pline->iflag] != 'C')
		if (!ft_check_flags(pline, (char*)msg))
			return (0);
	return (1);
}

char	ft_format_flags(t_pline *pline, const char *msg)
{
	ft_pline_init(pline);
	if (!ft_get_type(pline, msg))
		return (msg[pline->iflag]);
	pline->i += pline->iflag;
	ft_get_values(pline, msg[pline->iflag]);
	if (msg[pline->iflag] == 'x' || msg[pline->iflag] == 'X'
	|| msg[pline->iflag] == 'o' || msg[pline->iflag] == 'O')
		ft_print_ht(pline, msg[pline->iflag]);
	if (!pline->ht || (pline->ht && (msg[pline->iflag] != 'x'
	|| msg[pline->iflag] != 'X' || msg[pline->iflag] != 'o'
	|| msg[pline->iflag] != 'O')))
		ft_print_width(pline, msg[pline->iflag]);
	if (msg[pline->iflag] == 'd' || msg[pline->iflag] == 'i'
	|| msg[pline->iflag] == 'u' || (!pline->ht && (msg[pline->iflag] == 'X'
	|| msg[pline->iflag] == 'x' || msg[pline->iflag] == 'o'
	|| msg[pline->iflag] == 'O' || msg[pline->iflag] == 'p')))
		ft_print_prec(pline, msg[pline->iflag]);
	ft_print_space(pline, msg);
	return (msg[pline->iflag]);
}

void	ft_flags(t_pline *pline, const char *msg)
{
	char	c;

	c = ft_format_flags(pline, msg);
	if (c == 'd' || c == 'i' || c == 'D')
		ft_call_id_flag(pline, c);
	else if (c == 'u' || c == 'U')
		ft_call_u_flag(pline, c);
	else if (c == 'o' || c == 'O')
		ft_call_o_flag(pline, c);
	else if (c == 'x' || c == 'X')
		ft_call_x_flag(pline, c);
	else if (c == 'c' || c == 'C')
		ft_call_c_flag(pline, c);
	else if (c == 's' || c == 'S')
		ft_call_s_flag(pline, c);
	else if (c == 'f' || c == 'F')
		pline->i = ft_flag_f(pline);
	else if (c == 'p')
		pline->i = ft_flag_p(pline);
	else if (c == '%')
		pline->i = ft_flag_percent(pline);
	else if (--pline->dlen > 0 || pline->spaces)
		ft_invalid_flag(pline, c);
}
