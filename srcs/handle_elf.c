/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_elf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:00:48 by clanier           #+#    #+#             */
/*   Updated: 2018/03/05 20:06:32 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

void	handle_elf64(t_elf64 *elf)
{
	int			fd;

	if (elf->e_hdr->e_type != ET_EXEC || !elf->e_hdr->e_entry)
		exit_error(elf->e_hdr->e_type == ET_DYN ? ERR_NO_PIE : ERR_EXEC);
	prepare_injection(elf);
	if ((fd = open("woody", O_CREAT | O_RDWR | O_TRUNC, 0755)) <= 0)
		exit_error(ERR_UNKNOW);
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
	len = g_loader_sz + exec_load->p_memsz - exec_load->p_filesz + NEW_LEN;
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
