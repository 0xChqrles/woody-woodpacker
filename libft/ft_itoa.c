/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:32:31 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 07:59:39 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_number_len(int n)
{
	int	len;

	len = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_tochar(char *str, int n, int len)
{
	int neg;

	neg = 0;
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
		neg = 2;
	}
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
		neg = 1;
	}
	while ((len - neg) > 0)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_number_len(n);
	if ((str = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	str[len] = '\0';
	str = ft_tochar(str, n, len);
	return (str);
}
