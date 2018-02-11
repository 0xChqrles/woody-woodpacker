/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:57 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:53 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_wintlen(wchar_t chr)
{
	if (chr <= 0x7F)
		return (1);
	else if (chr <= 0x7FF)
		return (2);
	else if (chr <= 0xFFFF)
		return (3);
	else if (chr <= 0x10FFFF)
		return (4);
	return (0);
}

int	ft_wcharlen(wchar_t *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	while (str[i])
	{
		len += ft_wintlen(str[i]);
		i++;
	}
	return (len);
}

int	ft_l_strlen(t_pline *pline, wchar_t *str)
{
	int	i;
	int	len;
	int	oct;
	int	dotv;

	if (!str)
		return ((!pline->dotb || (pline->dotb && pline->dotv > 0)) ? 6 : 0);
	i = 0;
	len = 0;
	dotv = pline->dotv;
	while (str[i] && (!pline->dotb || (pline->dotb && dotv > 0)))
	{
		oct = ft_wintlen(str[i]);
		if (pline->dotb && (dotv -= oct) < 0)
			break ;
		len += ft_wintlen(str[i]);
		i++;
	}
	if (pline->dotb && pline->dotv < len)
		return (pline->dotv);
	return (len);
}

int	ft_s_strlen(t_pline *pline, char *str)
{
	int	i;

	if (!str)
		return ((!pline->dotb || (pline->dotb && pline->dotv > 0)) ? 6 : 0);
	i = 0;
	while (str[i])
		i++;
	if (pline->dotb && pline->dotv < i)
		return (pline->dotv);
	return (i);
}
