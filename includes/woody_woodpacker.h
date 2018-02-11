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

# define ERR_USAGE		"Invalid usage"
# define ERR_FILE 		"Invalid file"
# define ERR_ARCH 		"Not an ELF file"
# define ERR_ARCH_SIZE 	"Not a 64bit file"

# define AR_ELF		0b00000001
# define AR_64		0b00000010
# define AR_32		0b00000100

# define GET_ELFMAGIC(magic) ({\
	sprintf(magic, "%c%c%c%c", ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3);\
})

typedef		struct s_file
{
	uint8_t	arch;
	char	*filename;
	size_t	size;
	char	*ptr;
}			t_file;

#endif
