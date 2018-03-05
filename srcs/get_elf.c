/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:00:17 by clanier           #+#    #+#             */
/*   Updated: 2018/03/05 20:00:20 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody_woodpacker.h"

Elf64_Shdr	*get_last_exec_load_sect(Elf64_Shdr *s_hdr,
			int shnum, Elf64_Phdr *exec_load)
{
	Elf64_Shdr	*sect;
	Elf64_Shdr	*tmp;
	int			i;

	i = 0;
	sect = NULL;
	tmp = s_hdr;
	while (i++ < shnum)
	{
		if (tmp->sh_addr + tmp->sh_size
		>= exec_load->p_memsz + exec_load->p_vaddr)
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
	return (elf->strtab = elf->ptr
	+ (elf->s_hdr + elf->e_hdr->e_shstrndx)->sh_offset);
}
