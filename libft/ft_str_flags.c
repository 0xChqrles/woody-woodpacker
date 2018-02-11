/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:53 by clanier           #+#    #+#             */
/*   Updated: 2017/01/21 20:45:49 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_s(t_pline *pline)
{
	int	i;
	int	dup;

	i = 0;
	dup = 0;
	if (!pline->s && (dup = 1))
		pline->s = ft_strdup("(null)");
	while (pline->s[i] && (!pline->dotb
	|| (pline->dotb && pline->dotv-- > 0)) && ++pline->count)
		ft_putchar(pline->s[i++]);
	if (dup)
		free(pline->s);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

wchar_t	*ft_wchardup(wchar_t *s, int *dup)
{
	wchar_t	*str;
	int		i;

	i = 0;
	str = (wchar_t*)malloc(sizeof(wchar_t) * (ft_wcharlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	*dup = 1;
	return (str);
}

int		ft_flag_ls(t_pline *pline)
{
	int	i;
	int	oct;
	int	dup;

	i = 0;
	dup = 0;
	if (!pline->ls)
		pline->ls = ft_wchardup(L"(null)", &dup);
	while (pline->ls[i] && (!pline->dotb || (pline->dotb && pline->dotv > 0)))
	{
		oct = ft_wintlen(pline->ls[i]);
		if (pline->dotb && (pline->dotv -= oct) < 0)
			break ;
		ft_putwchar(pline->ls[i++]);
		pline->count += oct;
	}
	if (dup == 1 && pline->ls)
		free(pline->ls);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_lc(t_pline *pline, wchar_t c)
{
	pline->count += ft_putwchar(c);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}

int		ft_flag_c(t_pline *pline, int c)
{
	pline->count++;
	ft_putchar((unsigned char)c);
	while (pline->minus && pline->len-- > 0 && ++pline->count)
		ft_putchar(' ');
	return (++pline->i);
}
