/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 00:42:39 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:44 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_id_size(t_pline *pline, char c)
{
	if ((c == 'd' || c == 'i') && pline->ll)
		return (pline->size = ft_ll_nbrlen(pline,
		pline->llid = va_arg(pline->ap, long long int)));
	else if (c == 'D' || ((c == 'd' || c == 'i') && pline->l))
		return (pline->size = ft_l_nbrlen(pline,
		pline->lid = va_arg(pline->ap, long int)));
	else if ((c == 'd' || c == 'i') && pline->j)
		return (pline->size = ft_j_nbrlen(pline,
		pline->jid = va_arg(pline->ap, intmax_t)));
	else if ((c == 'd' || c == 'i') && pline->z)
		return (pline->size = ft_z_nbrlen(pline,
		pline->zid = va_arg(pline->ap, size_t)));
	else if ((c == 'd' || c == 'i') && pline->hh)
		return (pline->size = ft_hh_nbrlen(pline,
		pline->hhid = (signed char)va_arg(pline->ap, int)));
	else if ((c == 'd' || c == 'i') && pline->h)
		return (pline->size = ft_h_nbrlen(pline,
		pline->hid = (short int)va_arg(pline->ap, int)));
	else
		return (pline->size = ft_pnbrlen(pline,
		pline->id = va_arg(pline->ap, int)));
}

int		ft_get_u_size(t_pline *pline, char c)
{
	if ((c == 'u' || c == 'U') && pline->ll)
		return (pline->size = ft_ull_nbrlen(pline,
		pline->llu = va_arg(pline->ap, unsigned long long int)));
	else if ((c == 'u' || c == 'U') && pline->l)
		return (pline->size = ft_ul_nbrlen(pline,
		pline->lu = va_arg(pline->ap, unsigned long int)));
	else if ((c == 'u' || c == 'U') && pline->j)
		return (pline->size = ft_uj_nbrlen(pline,
		pline->ju = va_arg(pline->ap, uintmax_t)));
	else if ((c == 'u' || c == 'U') && pline->z)
		return (pline->size = ft_z_nbrlen(pline,
		pline->zu = va_arg(pline->ap, size_t)));
	else if ((c == 'u' || c == 'U') && pline->hh)
		return (pline->size = ft_uhh_nbrlen(pline,
		pline->hhu = (unsigned char)va_arg(pline->ap, int)));
	else if ((c == 'u' || c == 'U') && pline->h)
		return (pline->size = ft_uh_nbrlen(pline,
		pline->hu = (unsigned short int)va_arg(pline->ap, int)));
	else
		return (pline->size = ft_u_nbrlen(pline,
		pline->u = va_arg(pline->ap, unsigned int)));
}

int		ft_get_x_size(t_pline *pline, char c)
{
	if ((c == 'x' || c == 'X') && pline->ll)
		return (pline->size = ft_ull_hexlen(pline,
		pline->llx = va_arg(pline->ap, unsigned long long int)));
	else if ((c == 'x' || c == 'X') && pline->l)
		return (pline->size = ft_ul_hexlen(pline,
		pline->lx = va_arg(pline->ap, unsigned long int)));
	else if ((c == 'x' || c == 'X') && pline->j)
		return (pline->size = ft_uj_hexlen(pline,
		pline->jx = va_arg(pline->ap, uintmax_t)));
	else if ((c == 'x' || c == 'X') && pline->z)
		return (pline->size = ft_z_hexlen(pline,
		pline->zx = va_arg(pline->ap, size_t)));
	else if ((c == 'x' || c == 'X') && pline->hh)
		return (pline->size = ft_uhh_hexlen(pline,
		pline->hhx = (unsigned char)va_arg(pline->ap, int)));
	else if ((c == 'x' || c == 'X') && pline->h)
		return (pline->size = ft_uh_hexlen(pline,
		pline->hx = (unsigned short int)va_arg(pline->ap, int)));
	else
		return (pline->size = ft_u_hexlen(pline,
		pline->x = va_arg(pline->ap, unsigned int)));
}

int		ft_get_o_size(t_pline *pline, char c)
{
	if ((c == 'o' || c == 'O') && pline->ll)
		return (pline->size = ft_ull_octlen(pline,
		pline->llo = va_arg(pline->ap, unsigned long long int)));
	else if ((c == 'o' || c == 'O') && pline->l)
		return (pline->size = ft_ul_octlen(pline,
		pline->lo = va_arg(pline->ap, unsigned long int)));
	else if ((c == 'o' || c == 'O') && pline->j)
		return (pline->size = ft_uj_octlen(pline,
		pline->jo = va_arg(pline->ap, uintmax_t)));
	else if ((c == 'o' || c == 'O') && pline->z)
		return (pline->size = ft_z_octlen(pline,
		pline->zo = va_arg(pline->ap, size_t)));
	else if ((c == 'o' || c == 'O') && pline->hh)
		return (pline->size = ft_uhh_octlen(pline,
		pline->hho = (unsigned char)va_arg(pline->ap, int)));
	else if ((c == 'o' || c == 'O') && pline->h)
		return (pline->size = ft_uh_octlen(pline,
		pline->ho = (unsigned short int)va_arg(pline->ap, int)));
	else
		return (pline->size = ft_u_octlen(pline,
		pline->o = va_arg(pline->ap, unsigned int)));
}

int		ft_get_size(t_pline *pline, char c)
{
	if (c == 'c' || c == 'C')
		return (pline->size = 1);
	else if (c == 'd' || c == 'i' || c == 'D')
		return (ft_get_id_size(pline, c));
	else if (c == 'f' || c == 'F')
		return (pline->size = ft_floatlen(pline));
	else if (c == 'u' || c == 'U')
		return (ft_get_u_size(pline, c));
	else if (c == 'x' || c == 'X')
		return (ft_get_x_size(pline, c));
	else if (c == 'o' || c == 'O')
		return (ft_get_o_size(pline, c));
	else if (c == 'S' || (c == 's' && pline->l))
		return (pline->size = ft_l_strlen(pline,
		pline->ls = va_arg(pline->ap, wchar_t*)));
	else if (c == 's')
		return (pline->size = ft_s_strlen(pline,
		pline->s = va_arg(pline->ap, char*)));
	else if (c == 'p')
		return (pline->size = ft_ptrlen(pline,
		pline->p = va_arg(pline->ap, void*)));
	else if (c == '%')
		return (pline->size = 1);
	return (0);
}
