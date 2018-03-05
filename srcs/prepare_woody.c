#include "woody_woodpacker.h"

Elf64_Shdr	new_section(void)
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
