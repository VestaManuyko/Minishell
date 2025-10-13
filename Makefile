# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:10:06 by fpaglia           #+#    #+#              #
#    Updated: 2025/10/13 18:49:25 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
# FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -g3
INCLUDES = -Iinclude -Ilibs/libft
LINKS = -lreadline

# Relevant paths
SRC_DIR := source
OBJ_DIR := build
LIB_DIR := libs

# Groups of source files 
STRINGS = arr_deepcpy.c arr_print.c  arr_to_str.c arr_free.c arr_size.c \
		  str_clearquotes.c str_split_by_c.c str_split_by_set.c \
		  str_isquoted.c \
		  tar_popone.c tar_init.c tar_putone.c

ENVIRON = env_getid.c env_getvalue.c env_update_entry.c env_getkey.c

INPUT = prompt.c

INIT = init_shell.c

MAIN = main.c

# Add source paths to files 
STRINGS_SRC = $(addprefix $(SRC_DIR)/strings/, $(STRINGS))
ENVIRON_SRC = $(addprefix $(SRC_DIR)/environment/, $(ENVIRON))
INPUT_SRC = $(addprefix $(SRC_DIR)/input/, $(INPUT))
INIT_SRC = $(addprefix $(SRC_DIR)/init/, $(INIT))
MAIN_SRC = $(addprefix $(SRC_DIR)/, $(MAIN))

# Collect all the c file in one variable
SRC = $(STRINGS_SRC) $(ENVIRON_SRC) $(INPUT_SRC) $(INIT_SRC) $(MAIN_SRC)
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

LIBFT := $(LIB_DIR)/libft/libft.a
MINI := $(OBJ_DIR)/libmini.a
NAME := minishell 

$(NAME)  : $(OBJ) $(LIBFT) $(H_FILES) 
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(LINKS) -o $(NAME)
$(LIBFT) :
	make -C $(LIB_DIR)/libft libft.a
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $^
$(MINI) : $(OBJ) 
	@ mkdir -p $(dir $@)
	ar rcs $@ $^

.PHONY: all clean fclean re norm demo

all : $(NAME) $(LIBFT) $(MINI)

clean  :
	make -s -C $(LIB_DIR)/libft clean
	-rm -rf $(OBJ)

fclean : clean
	-rm -rf $(NAME) $(LIBFT) $(MINI) *.out

re : fclean all

norm:
	norminette -R CheckForForbiddenHeader $(SRC) 

demo: $(MINI) $(LIBFT) 
	make -f make-demo.mk 
dclean: 
	-rm  -rf demo/bin 
dre: dclean demo 
