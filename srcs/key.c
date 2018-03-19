/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:24:15 by clanier           #+#    #+#             */
/*   Updated: 2018/03/19 19:24:17 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

void	print_key(uint8_t *key)
{
	int	i;

	printf("key: ");
	i = 0;
	while (i < 16)
		printf("%02hhx ", key[i++]);
	printf("| %.16s\n", (char*)key);
}

int		generate_key(uint8_t *key)
{
	char	buf[16];
	int		fd;
	int		i;
	int		j;

	i = 0;
	if ((fd = open("/dev/urandom", 0)) < 0)
		exit_error(ERR_UNKNOW);
	while (i < 16 && read(fd, buf, 16) == 16)
	{
		j = 0;
		while (j < 16)
			if (ft_isalnum(buf[j++]))
			{
				key[i++] = buf[--j];
				break ;
			}
	}
	close(fd);
	return (i == 16 ? 0 : -1);
}
