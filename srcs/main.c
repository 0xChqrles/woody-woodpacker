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

Elf64_Shdr	*get_last_exec_load_sect(Elf64_Shdr *s_hdr, int shnum, Elf64_Phdr *exec_load)
{
	Elf64_Shdr	*sect;
	Elf64_Shdr	*tmp;
	int			i;

	i = 0;
	sect = NULL;
	tmp = s_hdr;
	while (i++ < shnum)
	{
		if (tmp->sh_addr + tmp->sh_size >= exec_load->p_memsz + exec_load->p_vaddr)
			sect = tmp;
		tmp++;
	}
	return (sect);
}

Elf64_Phdr	*get_last_exec_load(Elf64_Phdr *p_hdr, int phnum)
{
	Elf64_Phdr	*exec_load;
	Elf64_Phdr	*tmp;
	int			i;

	i = 0;
	exec_load = NULL;
	tmp = p_hdr;
	while (i++ < phnum)
	{
		if (tmp->p_type == PT_LOAD)
			exec_load = tmp;
		tmp++;
	}
	return (exec_load);
}

Elf64_Shdr	*get_sect_from_name(t_elf64 *elf, char *name)
{
	Elf64_Shdr	*tmp;
	int			i;

	i = 0;
	tmp = elf->s_hdr;
	while (i++ < elf->e_hdr->e_shnum)
	{
		if (!ft_strcmp(elf->strtab + tmp->sh_name, name))
			return (tmp);
		tmp++;
	}
	return (NULL);
}

void		*get_strtab(t_elf64 *elf)
{
	return (elf->strtab = elf->ptr + (elf->s_hdr + elf->e_hdr->e_shstrndx)->sh_offset);
}

void		shift_offset(t_elf64 *elf, uint64_t off, uint64_t size)
{
	Elf64_Shdr	*s_hdr;
	Elf64_Phdr	*p_hdr;
	int			i;

	i = 0;
	if (elf->e_hdr->e_shoff >= off)
	{
		elf->e_hdr->e_shoff += size;
		elf->s_hdr = (Elf64_Shdr*)(elf->ptr + elf->e_hdr->e_shoff);
	}
	if ((uint64_t)((char*)(elf->s_hdr +	elf->e_hdr->e_shstrndx) - elf->ptr) >= off
	&& (uint64_t)((char*)(elf->s_hdr) - elf->ptr) <= off)
		elf->e_hdr->e_shstrndx += size / sizeof(Elf64_Shdr);
	s_hdr = elf->s_hdr;
	while (i++ < elf->e_hdr->e_shnum)
		if ((s_hdr++)->sh_offset >= off)
			(s_hdr - 1)->sh_offset += size;
	i = 0;
	p_hdr = elf->p_hdr;
	while (i++ < elf->e_hdr->e_phnum)
		if ((p_hdr++)->p_offset >= off)
			(p_hdr - 1)->p_offset += size;
	elf->strtab = get_strtab(elf);
}

void	expand_elf_data(t_elf64 *elf, uint64_t off, uint64_t size)
{
	uint32_t	i;

	i = 0;
	if ((elf->free_size -= size) < 0 || off > elf->size)
		exit_error(ERR_UNKNOW);
	while (i++ < elf->size - off)
		elf->ptr[elf->size + size - i] = elf->ptr[elf->size - i];
	elf->ptr = ft_bzero(elf->ptr + off, size) - off;
	elf->size += size;
}

uint64_t	add_sect_name(t_elf64 *elf)
{
	Elf64_Shdr	*symtab;
	uint64_t	off;

	symtab = elf->s_hdr + elf->e_hdr->e_shstrndx;
	off = symtab->sh_offset + symtab->sh_size;
	expand_elf_data(elf, off, S_NAME_LEN);
	elf->ptr = ft_memcpy(elf->ptr + off, S_NAME, S_NAME_LEN - 1) - off;
	shift_offset(elf, off, S_NAME_LEN);
	symtab = elf->s_hdr + elf->e_hdr->e_shstrndx;
	symtab->sh_size += S_NAME_LEN;
	return (symtab->sh_size - S_NAME_LEN - 2);
}

void		prepare_s_data(char *s_data, Elf64_Shdr *text, uint32_t old, uint32_t new)
{
	uint32_t	jmp;

	if (!text)
		exit_error(ERR_WELL_FORMED);
	ft_memcpy(s_data, &loader, loader_sz);
	jmp = old - new - loader_sz + 0x10;
	ft_memcpy(s_data + loader_sz - 0x14, (char*)(&jmp), 4);
	ft_memcpy(s_data + loader_sz - 0x10, (char*)(&(text->sh_addr)), 8);
	ft_memcpy(s_data + loader_sz - 0x8, (char*)(&(text->sh_size)), 4);
}

uint64_t	add_sect_content(t_elf64 *elf, Elf64_Phdr *exec_load, Elf64_Shdr *sect)
{
	uint64_t	off;
	char		*s_data;
	uint32_t	align;

	if (!(s_data = malloc(loader_sz)))
		exit_error(ERR_UNKNOW);
	align = exec_load->p_memsz - exec_load->p_filesz;
	off = sect->sh_offset;
	if (sect->sh_type != SHT_NOBITS)
		off += sect->sh_size;
	prepare_s_data(s_data, get_sect_from_name(elf, ".text"),
	elf->e_hdr->e_entry, sect->sh_addr + sect->sh_size);
	expand_elf_data(elf, off, align + loader_sz);
	elf->ptr = ft_memcpy(elf->ptr + off + align, s_data, loader_sz) - off - align;
	shift_offset(elf, off, loader_sz + align);
	free(s_data);
	return (off + align);
}

Elf64_Shdr	fill_section(t_elf64 *elf, Elf64_Shdr new, Elf64_Phdr *exec_load)
{
	Elf64_Shdr	*sect;
	uint64_t	addr;

	if (!(sect = get_last_exec_load_sect(elf->s_hdr, elf->e_hdr->e_shnum, exec_load)))
		exit_error(ERR_UNKNOW);
	addr = sect->sh_addr + sect->sh_size;
	new.sh_offset = add_sect_content(elf, exec_load, sect);
	new.sh_name = add_sect_name(elf);
	new.sh_size = loader_sz;
	new.sh_addr = addr;
	elf->e_hdr->e_entry = addr;
	return (new);
}

void		set_pt_load_flags(Elf64_Phdr *p_hdr, int phnum)
{
	Elf64_Phdr	*tmp;
	int			i;

	i = 0;
	tmp = p_hdr;
	while (i++ < phnum)
	{
		if (tmp->p_type == PT_LOAD)
			tmp->p_flags = (PF_X | PF_W | PF_R);
		tmp++;
	}
}

Elf64_Shdr	*inject_section(t_elf64 *elf, Elf64_Shdr new, Elf64_Phdr *exec_load)
{
	Elf64_Shdr	*sect;
	uint64_t	off;

	if (!(sect = get_last_exec_load_sect(elf->s_hdr, elf->e_hdr->e_shnum, exec_load)))
		return (NULL);
	off = (char*)(++sect) - elf->ptr;
	expand_elf_data(elf, off, sizeof(Elf64_Shdr));
	elf->ptr = ft_memcpy(elf->ptr + off, (char*)(&new), sizeof(Elf64_Shdr)) - off;
	shift_offset(elf, off, sizeof(Elf64_Shdr));
	exec_load->p_memsz += new.sh_size;
	exec_load->p_filesz = exec_load->p_memsz;
	set_pt_load_flags(elf->p_hdr, elf->e_hdr->e_phnum);
	elf->e_hdr->e_shnum++;
	return (sect);
}

Elf64_Shdr	*prepare_injection(t_elf64 *elf)
{
	Elf64_Phdr	*exec_load;
	Elf64_Shdr	*woody;
	Elf64_Shdr	new;

	if (!(exec_load = get_last_exec_load(elf->p_hdr, elf->e_hdr->e_phnum)))
		exit_error(ERR_EXEC);
	new = new_section();
	new = fill_section(elf, new, exec_load);
	if (!(woody = inject_section(elf, new, exec_load)))
		exit_error(ERR_UNKNOW);
	return (woody);
}

void	cipher_s_text(t_elf64 *elf)
{
	Elf64_Shdr	*text;

	if (!(text = get_sect_from_name(elf, ".text")))
		exit_error(ERR_UNKNOW);
	cpr_algo(elf->ptr + text->sh_offset, text->sh_size);
}

void	handle_elf64(t_elf64 *elf)
{
	int			fd;

	if (elf->e_hdr->e_type != ET_EXEC || !elf->e_hdr->e_entry)
		exit_error(elf->e_hdr->e_type == ET_DYN ? ERR_NO_PIE : ERR_EXEC);
	prepare_injection(elf);
	cipher_s_text(elf);
	elf->e_hdr->e_phnum--;
	fd = open("woody", O_CREAT | O_RDWR | O_TRUNC, 0777);
	write(fd, (char*)elf->ptr, elf->size);
	close(fd);
}

void	init_elf64(t_file *file, t_elf64 *elf, uint64_t len, uint16_t opts)
{
	elf->ptr = ft_memcpy(elf->ptr, file->ptr, file->size);
	elf->ptr = ft_bzero(elf->ptr + file->size, len) - file->size;
	elf->e_hdr = (Elf64_Ehdr*)elf->ptr;
	elf->p_hdr = (Elf64_Phdr*)(elf->ptr + elf->e_hdr->e_phoff);
	elf->s_hdr = (Elf64_Shdr*)(elf->ptr + elf->e_hdr->e_shoff);
	elf->strtab = get_strtab(elf);
	elf->size = file->size;
	elf->free_size = len;
	elf->opts = opts;
}

t_elf64	*create_elf64(t_file *file, uint16_t opts)
{
	t_elf64		*elf;
	Elf64_Phdr	*exec_load;
	uint64_t	len;
	Elf64_Ehdr	*e_hdr;

	e_hdr = (Elf64_Ehdr*)file->ptr;
	if (file->size < e_hdr->e_phoff + sizeof(Elf64_Phdr) * e_hdr->e_phnum
	|| file->size < e_hdr->e_shoff + sizeof(Elf64_Shdr) * e_hdr->e_shnum)
		exit_error(ERR_WELL_FORMED);
	if (!(exec_load = get_last_exec_load((void*)file->ptr
	+ e_hdr->e_phoff, e_hdr->e_phnum)))
		exit_error(ERR_EXEC);
	len = NEW_LEN + loader_sz + exec_load->p_memsz - exec_load->p_filesz;
	if (!(elf = malloc(sizeof(t_elf64)))
	|| !(elf->ptr = malloc(file->size + len)))
		exit_error(ERR_UNKNOW);
	init_elf64(file, elf, len, opts);
	return (elf);
}

void	handle_file(t_file *file, uint16_t opts)
{
	t_elf64	*elf;

	if (!(file->arch & AR_ELF))
		exit_error(ERR_ARCH);
	else if (!(file->arch & AR_64))
		exit_error(ERR_ARCH_SIZE);
	elf = create_elf64(file, opts);
	free_file(file);
	handle_elf64(elf);
	free(elf);
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
			if (av[i][j] == OPT_F_V)
				*opts |= OPT_V;
			else
				return (-1);
		}
		if (!j)
			*opts = (((*opts >> 8) + 1) << 8 | (*opts & 0xff));
	}
	return (0);
}

int		main(int ac, char **av)
{
	uint16_t	opts;
	t_file		*file;
	int			i;
	int			j;

	i = 0;
	if ((j = get_options(ac, av, &opts)) < 0)
		return (exit_error(ERR_OPTION));
	while (j < (opts >> 8))
	{
		if (av[++i][0] == '-')
			continue ;
		if (init_file(&file, av[i]) < 0)
			return (exit_error(ERR_FILE));
		handle_file(file, opts);
		j++;
	}
}
