# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:10:06 by fpaglia           #+#    #+#              #
#    Updated: 2025/09/16 14:45:31 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
# FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -g3
INCLUDES = -Iinclude -Ilibs/libft -Ilibs/mlx 

SRC_DIR	:= src
OBJ_DIR := obj
LIB_DIR := libs
INC_DIR := include

C_FILES = 
H_FILES = $(INC_DIR)/


SRC_FILES = $(addprefix $(SRC_DIR)/, $(C_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIBFT := $(LIB_DIR)/libft/libft.a

all : $(NAME) $(LIBFT)

NAME := minishell 

$(NAME)  : $(OBJS) $(LIBFT) $(H_FILES) 
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LINKS) -o $(NAME)
$(LIBFT) :
	make -C $(LIB_DIR)/libft libft.a
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p obj
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $^

.PHONY: all clean fclean re norm

clean  :
	make -s -C $(LIB_DIR)/libft clean
	-rm -rf $(OBJS)
fclean : clean
	-rm -rf $(NAME) $(LIBFT) *.out
re : fclean all
norm:
	norminette -R CheckForForbiddenHeader $(SRC_FILES) $(H_FILES)

