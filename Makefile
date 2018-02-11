NAME		=	woody_woodpacker
SHEL		=	/bin/bash

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror

LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
SRCS_DIR	=	srcs/
SRCS_LIST	=	main.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR	=	objs/
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))
HEADERS		=	-I ./includes -I ./libft/includes -I ./includes/sys
LIBS		=	-L libft -lft

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@echo "\033[37mLinking...\033[0m"
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(LIBFT) :
	@make --no-print-directory -C $(LIBFT_DIR)

clean :
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean : clean
	@rm -rf $(LIBFT)
	@echo "\033[31mLib \033[1;31m$(notdir $(LIBFT))\033[1;0m\033[31m removed.\033[0m"
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re : fclean all
