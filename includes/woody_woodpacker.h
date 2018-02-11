/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:39:29 by clanier           #+#    #+#             */
/*   Updated: 2018/02/10 21:18:59 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_WOODPACKER_H
# define WOODY_WOODPACKER_H

# define ERR_USAGE "Invalid usage\n"
# define ERR_FILE "Invalid file\n"

# include "libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdlib.h"
# include "sys/stat.h"
# include "sys/mman.h"

typedef		struct s_file
{
	char	*filename;
	size_t	size;
	void	*ptr;
}			t_file;

#endif
