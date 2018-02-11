/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:27:49 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:27 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pnbrlen(t_pline *pline, int n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 1;
	if (n < 0)
	{
		pline->neg = true;
		i = 2;
		n = -n;
	}
	while (n /= 10)
		i++;
	return (i);
}

int	ft_u_nbrlen(t_pline *pline, unsigned int n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

int	ft_u_octlen(t_pline *pline, unsigned int n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 0;
	if (n == 0)
	{
		if (!pline->dotb)
			pline->ht = false;
		return (1);
	}
	while (n > 0)
	{
		n /= 8;
		i++;
	}
	return (i);
}

int	ft_u_hexlen(t_pline *pline, unsigned int n)
{
	int	i;

	if (n == 0 && pline->dotb && pline->dotv == 0)
		pline->nbase = true;
	i = 0;
	if (n == 0)
	{
		pline->ht = false;
		return (1);
	}
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

int	ft_ptrlen(t_pline *pline, void *ptr)
{
	return (ft_ul_hexlen(pline, (unsigned long int)ptr));
}
