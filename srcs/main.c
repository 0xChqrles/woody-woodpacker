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
	printf("\033[31;1m[ PACKER ]\033[0m : %s\n", err);
	exit (EXIT_FAILURE);
}

void	free_file(t_file *file)
{
	munmap(file->ptr, file->size);
	free(file);
}

uint8_t	get_arch(t_file *file)
{
	uint8_t	arch;
	char	magic[5];

	if (file->size < 5)
		return (0);
	arch = 0;
	GET_ELFMAGIC(magic);
	if (!ft_strncmp(file->ptr, magic, 4))
		arch |= AR_ELF;
	if (file->ptr[EI_CLASS] == ELFCLASS64)
		arch |= AR_64;
	else if (file->ptr[EI_CLASS] == ELFCLASS32)
		arch |= AR_32;
	return (arch);
}

int		init_file(t_file **file, char *filename)
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
	tmp->arch = get_arch(tmp);
	return (0);
}

void	handle_file(t_file *file)
{
	if (!(file->arch & AR_ELF))
		handle_error(ERR_ARCH);
	else if (!(file->arch & AR_64))
		handle_error(ERR_ARCH_SIZE);
}

int		main(int ac, char **av)
{
	t_file	*file;

	if (ac != 2)
		return (handle_error(ERR_USAGE));
	if (init_file(&file, av[1]) < 0)
		return (handle_error(ERR_FILE));
	handle_file(file);
	free_file(file);
}
