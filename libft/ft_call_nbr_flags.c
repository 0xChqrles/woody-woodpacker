/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_nbr_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:48:32 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:44:15 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_call_id_flag(t_pline *pline, char c)
{
	if ((c == 'i' || c == 'd') && pline->ll && !pline->nbase)
		pline->i = ft_flag_llid(pline);
	else if (c == 'D' || ((c == 'i' || c == 'd') && pline->l && !pline->nbase))
		pline->i = ft_flag_lid(pline);
	else if ((c == 'i' || c == 'd') && pline->j && !pline->nbase)
		pline->i = ft_flag_jid(pline);
	else if ((c == 'i' || c == 'd') && pline->z && !pline->nbase)
		pline->i = ft_flag_zid(pline);
	else if ((c == 'i' || c == 'd') && pline->hh && !pline->nbase)
		pline->i = ft_flag_hhid(pline);
	else if ((c == 'i' || c == 'd') && pline->h && !pline->nbase)
		pline->i = ft_flag_hid(pline);
	else if ((c == 'i' || c == 'd') && !pline->nbase)
		pline->i = ft_flag_id(pline);
	else
		pline->i++;
}

void	ft_call_u_flag(t_pline *pline, char c)
{
	if ((c == 'u' || c == 'U') && pline->ll)
		pline->i = ft_flag_llu(pline);
	else if ((c == 'u' || c == 'U') && pline->l)
		pline->i = ft_flag_lu(pline);
	else if ((c == 'u' || c == 'U') && pline->j)
		pline->i = ft_flag_ju(pline);
	else if ((c == 'u' || c == 'U') && pline->z)
		pline->i = ft_flag_zu(pline);
	else if ((c == 'u' || c == 'U') && pline->hh)
		pline->i = ft_flag_hhu(pline);
	else if ((c == 'u' || c == 'U') && pline->h)
		pline->i = ft_flag_hu(pline);
	else
		pline->i = ft_flag_u(pline);
}

void	ft_call_o_flag(t_pline *pline, char c)
{
	if ((c == 'o' || c == 'O') && pline->ll && !pline->nbase)
		pline->i = ft_flag_llo(pline);
	else if ((c == 'o' || c == 'O') && pline->l && !pline->nbase)
		pline->i = ft_flag_lo(pline);
	else if ((c == 'o' || c == 'O') && pline->j && !pline->nbase)
		pline->i = ft_flag_jo(pline);
	else if ((c == 'o' || c == 'O') && pline->z && !pline->nbase)
		pline->i = ft_flag_zo(pline);
	else if ((c == 'o' || c == 'O') && pline->hh && !pline->nbase)
		pline->i = ft_flag_hho(pline);
	else if ((c == 'o' || c == 'O') && pline->h && !pline->nbase)
		pline->i = ft_flag_ho(pline);
	else if ((c == 'o' || c == 'O') && !pline->nbase)
		pline->i = ft_flag_o(pline);
	else
		pline->i++;
}

void	ft_call_x_flag(t_pline *pline, char c)
{
	if ((c == 'x' || c == 'X') && pline->ll && !pline->nbase)
		pline->i = ft_flag_llx(pline, c);
	else if ((c == 'x' || c == 'X') && pline->l && !pline->nbase)
		pline->i = ft_flag_lx(pline, c);
	else if ((c == 'x' || c == 'X') && pline->j && !pline->nbase)
		pline->i = ft_flag_jx(pline, c);
	else if ((c == 'x' || c == 'X') && pline->z && !pline->nbase)
		pline->i = ft_flag_zx(pline, c);
	else if ((c == 'x' || c == 'X') && pline->hh && !pline->nbase)
		pline->i = ft_flag_hhx(pline, c);
	else if ((c == 'x' || c == 'X') && pline->h && !pline->nbase)
		pline->i = ft_flag_hx(pline, c);
	else if ((c == 'x' || c == 'X') && !pline->nbase)
		pline->i = ft_flag_x(pline, c);
	else
		pline->i++;
}
