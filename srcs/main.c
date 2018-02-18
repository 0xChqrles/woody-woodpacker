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

Elf64_Phdr	*get_inject_pt_load(t_elf64 *elf)
{
	Elf64_Phdr	*tmp;
	Elf64_Phdr	*pt_load;
	int	i;

	i = 0;
	pt_load = NULL;
	tmp = elf->p_hdr;
	while (i < elf->e_hdr->e_phnum)
	{
		if (tmp->p_type == PT_LOAD)
			pt_load = tmp;
		tmp = (Elf64_Phdr*)((size_t)tmp + sizeof(Elf64_Phdr));
		i++;
	}
	return (pt_load);
}

Elf64_Shdr	*get_inject_sect(t_elf64 *elf, Elf64_Phdr *pt_load)
{
	Elf64_Shdr	*tmp;
	Elf64_Shdr	*sect;
	int	i;

	i = 0;
	sect = NULL;
	tmp = elf->s_hdr;
	while (i < elf->e_hdr->e_shnum)
	{
		if (tmp->sh_addr + tmp->sh_size >= pt_load->p_vaddr + pt_load->p_memsz)
			sect = tmp;
		tmp = (Elf64_Shdr*)((size_t)tmp + sizeof(Elf64_Shdr));
		i++;
	}
	return (sect);
}

Elf64_Shdr	new_section()
{
	Elf64_Shdr	new;

	new.sh_name = 0;
	new.sh_type = SHT_PROGBITS;
	new.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	new.sh_addr = 0;
	new.sh_offset = 0;
	new.sh_size = 0;
	new.sh_link = 0;
	new.sh_info = 0;
	new.sh_addralign = 16;
	new.sh_entsize = 0;
	return (new);
}

Elf64_Shdr	fill_section(t_elf64 *elf, Elf64_Shdr new, Elf64_Phdr *pt_load, Elf64_Shdr *sect)
{
	elf->e_hdr->e_shnum++;
	new.sh_name = sect->sh_name;
	new.sh_addr = pt_load->p_vaddr + pt_load->p_memsz;
	new.sh_offset = pt_load->p_offset + pt_load->p_filesz - 10;
	new.sh_size = 10;
	return (new);
}

void	write_sections(t_elf64 *elf, int fd)
{
//	Elf64_Shdr	*s_hdr;
	size_t		off;

//	s_hdr = elf->s_hdr;
	off = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * elf->e_hdr->e_phnum;
	write(fd, elf->ptr + off, elf->e_hdr->e_shoff - off);
}

void	create_woody(t_elf64 *elf, Elf64_Shdr new, Elf64_Phdr *pt_load)
{
	Elf64_Phdr	*p_hdr;
	Elf64_Shdr	*s_hdr;
	int			i;
	int			fd;

	i = 0;
	fd = open("woody", O_CREAT | O_RDWR | O_TRUNC, 0777);
	write(fd, (char*)elf->e_hdr, sizeof(Elf64_Ehdr));
	p_hdr = elf->p_hdr;
	while (i++ < elf->e_hdr->e_phnum)
	{
		write(fd, (char*)p_hdr, sizeof(Elf64_Phdr));
		p_hdr++;
	}
	s_hdr = elf->s_hdr;
	i = 0;
	write_sections(elf, fd);
	while (i++ < elf->e_hdr->e_shnum)
	{
		write(fd, (char*)s_hdr, sizeof(Elf64_Shdr));
		s_hdr++;
	}
	(void)pt_load;
	write(fd, (char*)(&new), sizeof(Elf64_Shdr));
}

void		prepare_injection(t_elf64 *elf)
{
	Elf64_Phdr	*pt_load;
	Elf64_Shdr	*sect;
	Elf64_Shdr	new;

	if (!(pt_load = get_inject_pt_load(elf)) || !(sect = get_inject_sect(elf, pt_load)))
		exit_error(ERR_WELL_FORMED);
	new = new_section();
	new = fill_section(elf, new, pt_load, sect);
	create_woody(elf, new, pt_load);
}

uint64_t	get_strtab_ndx(t_elf64 *elf)
{
	Elf64_Shdr	*s_hdr;
	int			i;

	i = 0;
	s_hdr = elf->s_hdr;
	while (i < elf->e_hdr->e_shnum)
	{
		if (i == elf->e_hdr->e_shstrndx)
			return (s_hdr->sh_offset);
		s_hdr = (Elf64_Shdr*)((size_t)s_hdr + sizeof(Elf64_Shdr));
		i++;
	}
	return (0);
}

void	print_strtab(t_elf64 *elf)
{
	Elf64_Shdr	*s_hdr;
	int			i;

	i = 0;
	s_hdr = elf->s_hdr;
	while (i++ < elf->e_hdr->e_shnum)
	{
		printf("%s\n", &elf->strtab[s_hdr->sh_name]);
		s_hdr++;
	}
}

void	handle_elf64(t_elf64 *elf)
{
	if ((elf->e_hdr->e_type != ET_DYN && elf->e_hdr->e_type != ET_EXEC) || !elf->e_hdr->e_entry)
		exit_error(ERR_EXEC);
	if (!(elf->strtab_ndx = get_strtab_ndx(elf)))
		exit_error(ERR_WELL_FORMED);
	elf->strtab = elf->ptr + elf->strtab_ndx;
	prepare_injection(elf);
	print_strtab(elf);
}

t_elf64	*create_elf64(t_file *file)
{
	t_elf64	*elf;

	if (!(elf = malloc(sizeof(t_elf64))) || !(elf->ptr = malloc(file->size)))
		exit_error(ERR_UNKNOW);
	elf->ptr = memcpy(elf->ptr, file->ptr, file->size);
	elf->e_hdr = (Elf64_Ehdr*)elf->ptr;
	elf->p_hdr = (Elf64_Phdr*)(elf->ptr + elf->e_hdr->e_phoff);
	elf->s_hdr = (Elf64_Shdr*)(elf->ptr + elf->e_hdr->e_shoff);
	if (check_size(file, elf->e_hdr->e_phoff + sizeof(Elf64_Phdr) * elf->e_hdr->e_phnum, F_BEGIN) < 0
	|| check_size(file, elf->e_hdr->e_shoff + sizeof(Elf64_Shdr) * elf->e_hdr->e_shnum, F_BEGIN) < 0)
		exit_error(ERR_WELL_FORMED);
	elf->size = file->size;
	return (elf);
}

void	handle_file(t_file *file)
{
	t_elf64	*elf;

	if (!(file->arch & AR_ELF))
		exit_error(ERR_ARCH);
	else if (!(file->arch & AR_64))
		exit_error(ERR_ARCH_SIZE);
	elf = create_elf64(file);
	free_file(file);
	handle_elf64(elf);
}

int		main(int ac, char **av)
{
	t_file	*file;

	if (ac != 2)
		return (exit_error(ERR_USAGE));
	if (init_file(&file, av[1]) < 0)
		return (exit_error(ERR_FILE));
	handle_file(file);
}
