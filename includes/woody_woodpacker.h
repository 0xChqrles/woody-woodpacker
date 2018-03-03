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
# define ERR_UNKNOW			"An error has occurred"

# define AR_ELF		0b00000001
# define AR_64		0b00000010
# define AR_32		0b00000100

# define S_NAME		".woody"
# define S_NAME_LEN	ft_strlen(S_NAME) + 1

# define S_DATA		"\x9c\x50\x57\x56\x54\x52\x51\xbf\x01\x00\x00\x00\x48\x8d\x35\x0c\x00\x00\x00\xba\x0e\x00\x00\x00\x48\x89\xf8\x0f\x05\xeb\x0f\x2e\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x2e\x2e\x0a\x00\x59\x5a\x5c\x5e\x5f\x58\x9d\xe9%c%c%c%c\x1b"
# define S_DATA_LEN	datalen(S_DATA) - 4

# define NEW_LEN	S_NAME_LEN + S_DATA_LEN + sizeof(Elf64_Shdr)

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
