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

int		exit_error(const char *err)
{
	printf("\033[31;1m[ PACKER ]\033[0m : %s\n", err);
	exit (EXIT_FAILURE);
}

void	free_file(t_file *file)
{
	munmap(file->ptr, file->size);
	free(file);
}

int		check_size(t_file *file, int64_t size, uint8_t flag)
{
	if (flag & F_BEGIN && file->size - size < 0)
		return (-1);
	if (flag & F_OFFSET && (file->free_size -= size) < 0)
		return (-1);
	return (0);
}

void	get_elfmagic(char *magic)
{
	sprintf(magic, "%c%c%c%c", ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3);
}

uint8_t	get_arch(t_file *file)
{
	uint8_t	arch;
	char	magic[5];

	if (file->size < EI_NIDENT)
		return (0);
	arch = 0;
	get_elfmagic(magic);
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
	tmp->free_size = buf.st_size;
	tmp->filename = filename;
	tmp->arch = get_arch(tmp);
	return (0);
}

void		dump_section_name(t_file *file, Elf64_Ehdr *e_hdr)
{
	Elf64_Shdr	*s_hdr;
	int	i;

	i = 0;
	s_hdr = (Elf64_Shdr*)(file->ptr + e_hdr->e_shoff);
	while (i < e_hdr->e_shnum) {
		if (check_size(file, e_hdr->e_shoff + sizeof(Elf64_Shdr) * (i + 1), F_BEGIN) < 0)
			exit_error(ERR_WELL_FORMED);
		printf("%s\n", (char*)((size_t)file->ptr + file->strtab_ndx + s_hdr->sh_name));
		s_hdr = (Elf64_Shdr*)((size_t)s_hdr + sizeof(Elf64_Shdr));
		i++;
	}
}

uint64_t	get_strtab_ndx(t_file *file, Elf64_Ehdr *e_hdr)
{
	Elf64_Shdr	*s_hdr;
	int			i;

	i = 0;
	s_hdr = (Elf64_Shdr*)(file->ptr + e_hdr->e_shoff);
	while (i < e_hdr->e_shnum)
	{
		if (check_size(file, e_hdr->e_shoff + sizeof(Elf64_Shdr) * (i + 1), F_BEGIN) < 0)
			return (0);
		if (i == e_hdr->e_shstrndx)
			return (s_hdr->sh_offset);
		s_hdr = (Elf64_Shdr*)((size_t)s_hdr + sizeof(Elf64_Shdr));
		i++;
	}
	return (0);
}

void	handle_elf64(t_file *file)
{
	Elf64_Ehdr	*e_hdr;

	if (check_size(file, sizeof(Elf64_Ehdr), F_BEGIN) < 0)
		exit_error(ERR_WELL_FORMED);
	e_hdr = (Elf64_Ehdr*)file->ptr;
	if ((e_hdr->e_type != ET_DYN && e_hdr->e_type != ET_EXEC) || !e_hdr->e_entry)
		exit_error(ERR_EXEC);
	if (!(file->strtab_ndx = get_strtab_ndx(file, e_hdr)))
		exit_error(ERR_WELL_FORMED);
	file->strtab = file->ptr + file->strtab_ndx;
	dump_section_name(file, e_hdr);
}

void	handle_file(t_file *file)
{
	if (!(file->arch & AR_ELF))
		exit_error(ERR_ARCH);
	else if (!(file->arch & AR_64))
		exit_error(ERR_ARCH_SIZE);
	handle_elf64(file);
}

int		main(int ac, char **av)
{
	t_file	*file;

	if (ac != 2)
		return (exit_error(ERR_USAGE));
	if (init_file(&file, av[1]) < 0)
		return (exit_error(ERR_FILE));
	handle_file(file);
	free_file(file);
}
