/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:49:07 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:47:07 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_sign(t_pline *pline, char c)
{
	if ((c == 'i' || c == 'd' || c == 'D')
	&& ((pline->dotv > 0 && pline->len < 1)
	|| (pline->zero && pline->len > 0)) && pline->neg && !pline->csign)
	{
		ft_putchar('-');
		pline->count++;
		if (pline->ll)
			pline->llid = -pline->llid;
		else if (pline->l)
			pline->lid = -pline->lid;
		else if (pline->j)
			pline->jid = -pline->jid;
		else if (pline->h)
			pline->hid = -pline->hid;
		else if (pline->hh)
			pline->hhid = -pline->hhid;
		else if (!pline->z)
			pline->id = -pline->id;
		pline->csign = true;
	}
}
