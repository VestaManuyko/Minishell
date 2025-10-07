# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:10:06 by fpaglia           #+#    #+#              #
#    Updated: 2025/10/07 17:27:09 by vmanuyko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
# FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -g3
INCLUDES = -Iinclude -Ilibs/libft

# Relevant paths
SRC_DIR := source
OBJ_DIR := build
LIB_DIR := libs

# Groups of source files 
STRINGS = str_isquoted.c
EXAMPLE = 

# Add source paths to files 
STRINGS_SRC = $(addprefix $(SRC_DIR)/strings/, $(STRINGS))
EXAMPLE_SRC = $(addprefix $(SRC_DIR)/example/, $(EXAMPLE))

# Collect all the c file in one variable
SRC = $(STRINGS_SRC) $(EXAMPLE_SRC)
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

LIBFT := $(LIB_DIR)/libft/libft.a

NAME := minishell 

$(NAME)  : $(OBJ) $(LIBFT) $(H_FILES) 
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)
$(LIBFT) :
	make -C $(LIB_DIR)/libft libft.a
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $^

.PHONY: all clean fclean re norm demo

all : $(NAME) $(LIBFT)

clean  :
	make -s -C $(LIB_DIR)/libft clean
	-rm -rf $(OBJS)

fclean : clean
	-rm -rf $(NAME) $(LIBFT) *.out

re : fclean all

norm:
	norminette -R CheckForForbiddenHeader $(SRC) 

demo: $(OBJ) 
	make -f make-demo.mk 
dclean: 
	-rm  -rf demo/bin 

dre: dclean demo 
