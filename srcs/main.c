/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:37:04 by clanier           #+#    #+#             */
/*   Updated: 2018/02/10 21:26:09 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

int		handle_error(const char *err)
{
	printf("\033[31;1m[ PACKER ]\033[0m : %s", err);
	exit (EXIT_FAILURE);
}

void	free_file(t_file *file)
{
	munmap(file->ptr, file->size);
	free(file);
}

int		handle_file(t_file **file, char *filename)
{
	t_file		*tmp;
	int			fd;
	struct stat	buf;

	*file = malloc(sizeof(t_file));
	tmp = *file;
	if ((fd = open(filename, O_RDONLY)) < 1 || fstat(fd, &buf) < 0)
		return (-1);
	if ((tmp->ptr = mmap(0, buf.st_size,
	PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	tmp->size = buf.st_size;
	tmp->filename = filename;
	return (0);
}

int		main(int ac, char **av)
{
	t_file	*file;

	if (ac != 2)
		return (handle_error(ERR_USAGE));
	if (handle_file(&file, av[1]) < 0)
		return (handle_error(ERR_FILE));
	free_file(file);
}
