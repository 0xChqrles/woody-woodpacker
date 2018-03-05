/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_elf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 19:59:49 by clanier           #+#    #+#             */
/*   Updated: 2018/03/05 19:59:55 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

void	shift_offset(t_elf64 *elf, uint64_t off, uint64_t size)
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
	if ((uint64_t)((char*)(elf->s_hdr
	+ elf->e_hdr->e_shstrndx) - elf->ptr) >= off
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
