# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 17:20:15 by wdebs             #+#    #+#              #
#    Updated: 2017/03/02 00:31:44 by wdebs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INC_DIR = includes
C_DIRS = $(shell find . -type d -follow -print | grep -v obj | grep -v includes)
C_FILES = $(shell find . -type f -follow -print | grep "\.c")

O_DIR = obj
O_DIRS = $(C_DIRS:.%=$(O_DIR)%)
O_FILES = $(C_FILES:.%.c=$(O_DIR)%.o)

IFLAGS = -I $(INC_DIR) -I includes -I libft/includes
FLAGS = -Wall -Werror -Wextra -g

CC = gcc $(FLAGS)
LIBFLAGS = -L./libft -lft
RM = /bin/rm -f

all: $(NAME)

$(NAME) : $(O_FILES)
	@make -C ./libft
	@$(CC) -o $@ $^ $(LIBFLAGS)

$(O_DIR)/%.o: ./%.c
	@mkdir -p $(O_DIRS)
	@$(CC) $(IFLAGS) -o $@ -c $<

clean:
	@$(RM) -r $(O_DIR)
	@make -C ./libft clean

fclean: clean
	@$(RM) $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re	
