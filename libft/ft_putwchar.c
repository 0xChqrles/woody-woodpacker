/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:53 by clanier           #+#    #+#             */
/*   Updated: 2017/01/19 21:28:54 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwchar(wchar_t chr)
{
	int	i;

	i = 1;
	if (chr <= 0x7F)
		ft_putchar(chr);
	else if (chr <= 0x7FF && (i = 2))
	{
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF && (i = 3))
	{
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF && (i = 4))
	{
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	return (i);
}
