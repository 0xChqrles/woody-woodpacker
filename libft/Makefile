# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 05:41:01 by clanier           #+#    #+#              #
#    Updated: 2017/02/03 12:54:02 by clanier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SHEL		=	/bin/sh
CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror
SRCS_DIR	=	./
SRCS_LIST	=	ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putchar.c \
				ft_putendl_fd.c \
				ft_putendl.c \
				ft_putnbr_fd.c \
				ft_putnbr.c \
				ft_uputnbr.c \
				ft_putstr_fd.c \
				ft_putstr.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strcdup.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnequ.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strtrim.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_pow.c \
				ft_sqrt.c \
				ft_abs.c \
				ft_putchar_tab.c \
				ft_putnbr_tab.c \
				ft_nbrset_tab.c \
				ft_nbrtotal_tab.c \
				ft_realloc.c \
				ft_freejoin.c \
				ft_putwchar.c \
				get_next_line.c \
				ft_call_flags.c \
				ft_check_flags.c \
				ft_parse_flags.c \
				ft_extra_flags.c \
				ft_f_flags.c \
				ft_f_lens.c \
				ft_flags.c \
				ft_flags_funcs.c \
				ft_get_flags.c \
				ft_get_size.c \
				ft_h_flags.c \
				ft_h_lens.c \
				ft_hh_flags.c \
				ft_hh_lens.c \
				ft_j_flags.c \
				ft_j_lens.c \
				ft_l_flags.c \
				ft_l_lens.c \
				ft_lens.c \
				ft_ll_flags.c \
				ft_ll_lens.c \
				ft_print_flags.c \
				ft_printf.c \
				ft_str_flags.c \
				ft_str_lens.c \
				ft_z_flags.c \
				ft_z_lens.c \
				ft_call_nbr_flags.c \
				ft_call_str_flags.c \
				ft_invalid_flags.c \
				ft_nbrlen.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR	=	./
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))
HEADERS		=	-I./includes

all : $(NAME)

.PHONY: all clean

$(NAME) : $(OBJS)
	@echo "\033[37mLinking...\033[0m"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[32mLibrary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $^
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

clean :
	@rm -rf $(OBJS)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[31mLib \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re : fclean all
