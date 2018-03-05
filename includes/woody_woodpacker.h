/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:39:29 by clanier           #+#    #+#             */
/*   Updated: 2018/02/11 22:49:20 by clanier          ###   ########.fr       */
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

# define OPT_F_V	'v'
# define OPT_V		0b00000001

# define ERR_USAGE			"Invalid usage"
# define ERR_OPTION			"Invalid option"
# define ERR_FILE 			"Invalid file"
# define ERR_ARCH 			"Not an ELF file"
# define ERR_ARCH_SIZE 		"Not a 64bit file"
# define ERR_EXEC 			"Not an executable file"
# define ERR_WELL_FORMED	"Not well-formed"
# define ERR_NO_PIE			"This binary is not ET_EXEC, try to recompile with -no-pie flag"
# define ERR_UNKNOW			"An error has occurred"

# define AR_ELF		0b00000001
# define AR_64		0b00000010
# define AR_32		0b00000100

# define S_NAME		".woody"
# define S_NAME_LEN	ft_strlen(S_NAME) + 1

# define NEW_LEN	S_NAME_LEN + sizeof(Elf64_Shdr)

void			loader(void);
extern uint32_t	loader_sz;

void			cpr_algo(void *text, size_t sz);

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

#endif
