/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:39:29 by clanier           #+#    #+#             */
/*   Updated: 2018/03/05 20:05:44 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_WOODPACKER_H
# define WOODY_WOODPACKER_H

# include "libft.h"
# include <elf.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define OPT_C_H	'h'
# define OPT_H		0b00000001

# define ERR_USAGE			"Invalid usage try with -h option"
# define ERR_FILE 			"Invalid file"
# define ERR_ARCH 			"Not an ELF file"
# define ERR_ARCH_SIZE 		"Not a 64bit file"
# define ERR_EXEC 			"Not an executable file"
# define ERR_WELL_FORMED	"Not well-formed"
# define ERR_NO_PIE			"This executable is not ET_EXEC but ET_DYN"
# define ERR_UNKNOW			"An error has occurred"

# define AR_ELF		0b00000001
# define AR_64		0b00000010
# define AR_32		0b00000100

# define S_NAME		".woody"
# define S_NAME_LEN	ft_strlen(S_NAME) + 1

# define NEW_LEN	S_NAME_LEN + sizeof(Elf64_Shdr);

void			loader(void);
extern uint32_t	g_loader_sz;

typedef struct	s_file
{
	uint8_t		arch;
	char		*filename;
	size_t		size;
	int64_t		free_size;
	char		*ptr;
}				t_file;

typedef struct	s_elf64
{
	char		*ptr;
	size_t		size;
	int			free_size;
	Elf64_Ehdr	*e_hdr;
	Elf64_Phdr	*p_hdr;
	Elf64_Shdr	*s_hdr;
	char		*strtab;
	uint16_t	opts;
}				t_elf64;

void			shift_offset(t_elf64 *elf, uint64_t off, uint64_t size);
void			expand_elf_data(t_elf64 *elf, uint64_t off, uint64_t size);
Elf64_Shdr		*get_last_exec_load_sect(Elf64_Shdr *s_hdr,
				int shnum, Elf64_Phdr *exec_load);
Elf64_Phdr		*get_last_exec_load(Elf64_Phdr *p_hdr, int phnum);
Elf64_Shdr		*get_sect_from_name(t_elf64 *elf, char *name);
void			*get_strtab(t_elf64 *elf);
void			handle_elf64(t_elf64 *elf);
void			init_elf64(t_file *file,
				t_elf64 *elf, uint64_t len, uint16_t opts);
t_elf64			*create_elf64(t_file *file, uint16_t opts);
void			handle_file(t_file *file, uint16_t opts);
void			free_file(t_file *file);
void			get_elfmagic(char *magic);
uint8_t			get_arch(t_file *file);
int				init_file(t_file **file, char *filename);
uint64_t		add_sect_name(t_elf64 *elf);
void			prepare_s_data(t_elf64 *elf, char *s_data,
				Elf64_Shdr *text, uint32_t new);
uint64_t		add_sect_content(t_elf64 *elf,
				Elf64_Phdr *exec_load, Elf64_Shdr *sect);
Elf64_Shdr		fill_section(t_elf64 *elf,
				Elf64_Shdr new, Elf64_Phdr *exec_load);
Elf64_Shdr		*inject_section(t_elf64 *elf,
				Elf64_Shdr new, Elf64_Phdr *exec_load);
void			exit_error(const char *err);
int				get_options(int ac, char **av, uint16_t *opts);
int				main(int ac, char **av);
Elf64_Shdr		new_section(void);
void			set_pt_load_flags(Elf64_Phdr *p_hdr, int phnum);
Elf64_Shdr		*prepare_injection(t_elf64 *elf);
void			cpr_algo(void *text, size_t sz, uint8_t *key);
int				generate_key(uint8_t *key);
void			print_key(uint8_t *key);

#endif
