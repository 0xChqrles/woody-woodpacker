/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 05:15:03 by clanier           #+#    #+#             */
/*   Updated: 2016/11/07 05:31:40 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_sqrt(int n)
{
	float	sqrt;
	float	size;
	int		i;

	i = 0;
	size = 11585.5;
	sqrt = 23171;
	while (i < 1000)
	{
		if (sqrt * sqrt > n)
			sqrt -= size;
		else if (sqrt * sqrt < n)
			sqrt += size;
		size /= 2;
		i++;
	}
	return (sqrt);
}
