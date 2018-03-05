/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:37:04 by clanier           #+#    #+#             */
/*   Updated: 2018/03/05 18:31:18 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

void	exit_error(const char *err)
{
	printf("\033[31;1m[ PACKER ]\033[0m : %s\n", err);
	exit(EXIT_FAILURE);
}

int	get_options(int ac, char **av, uint16_t *opts)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac && !(j = 0))
	{
		while (av[i][0] == '-' && av[i][++j])
		{
			if (av[i][j] == OPT_C_H)
				*opts |= OPT_H;
			else
				return (-1);
		}
		if (!j && !(*opts >> 8))
			*opts = (((*opts >> 8) | i) << 8 | (*opts & 0xff));
		else if (!j)
			return (-1);
	}
	return ((*opts >> 8) || (*opts & OPT_H) ? 0 : -1);
}

void	display_help(void)
{
	printf("Usage: ./woody_woodpacker [USAGES]... [ELF-64 EXECUTABLE]...\n");
	printf("Woody Woodpacker is an ELF-64 packer\n\n");
	printf("  -h\t\tDisplay this help\n\n");
	printf("Woody Woodpacker will create a new executable named \"woody\"\n");
	printf("\"woody\" will have the same behavior than the origianl binary\n");
	printf("after having write \"....WOODY....\\n\" on stdout\n");
}

int		main(int ac, char **av)
{
	uint16_t	opts;
	t_file		*file;

	if (get_options(ac, av, &opts) < 0)
		exit_error(ERR_USAGE);
	if (opts & OPT_H)
	{
		display_help();
		return (0);
	}
	if (init_file(&file, av[(opts >> 8)]) < 0)
		exit_error(ERR_FILE);
	handle_file(file, opts);
}
