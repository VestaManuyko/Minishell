# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:10:06 by fpaglia           #+#    #+#              #
#    Updated: 2025/11/05 12:17:01 by vmanuyko         ###   ########.fr        #
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

# All the h_files
H_INCLUDES = minishell.h err_mes.h ms_commands.h ms_environment.h ms_init.h \
			ms_redirections.h ms_strings.h ms_structs_support.h ms_structs.h
# Groups of source files 
STRINGS = arr_deepcpy.c arr_print.c  arr_to_str.c arr_free.c arr_size.c \
		  arr_double.c \
		  str_split_by_set.c str_isquoted.c \
		  str_clearquotes.c \
		  str_expand.c str_expand_quotes.c str_expand_dollar.c \
		  tar_init.c tar_free.c tar_print.c \
		  tar_popone.c tar_linkone.c \
		  tar_putstr.c tar_putred.c 

ENVIRON = env_getid.c env_getkey.c env_getvalue.c env_getpaths.c \
		  env_entry_update.c  env_entry_remove.c  

INPUT = prompt.c heredoc.c handle_heredoc.c

INIT = init_shell.c free_shell.c reset_shell.c \
	   signal.c init_builtin.c

MAIN = main.c

REDIRECT = red_init.c red_free.c \
		   red_perror.c red_str2struct.c red_raw2val.c

EXEC = exec_prog.c echo.c bltn.c
		   
COMMANDS = programs_init.c programs_free.c \
		   programs_populate.c  program_validate.c programs_print.c \
		   cmd_perror.c \
		   cmd_validate_pipes.c \
		   cmd_str2prog.c \
		   cmd_split_tokens.c cmd_parse_progs.c cmd_parse_redirect.c \
		   cmd_fillheredoc.c 

# Add source paths to files 
STRINGS_SRC = $(addprefix $(SRC_DIR)/strings/, $(STRINGS))
ENVIRON_SRC = $(addprefix $(SRC_DIR)/environment/, $(ENVIRON))
INPUT_SRC = $(addprefix $(SRC_DIR)/input/, $(INPUT))
REDIRECT_SRC = $(addprefix $(SRC_DIR)/redirections/, $(REDIRECT))
COMMANDS_SRC = $(addprefix $(SRC_DIR)/commands/, $(COMMANDS))
INIT_SRC = $(addprefix $(SRC_DIR)/init/, $(INIT))
EXEC_SRC = $(addprefix $(SRC_DIR)/execution/, $(EXEC))
MAIN_SRC = $(addprefix $(SRC_DIR)/, $(MAIN))

# Collect all the c file in one variable
SRC = $(STRINGS_SRC) $(ENVIRON_SRC) $(INPUT_SRC) $(REDIRECT_SRC) \
	  $(COMMANDS_SRC) $(INIT_SRC) $(EXEC_SRC)
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

H_FILES = $(addprefix include/, $(H_INCLUDES))

LIBFT := $(LIB_DIR)/libft/libft.a
MINI := $(OBJ_DIR)/libmini.a
NAME := minishell

$(NAME)  : $(LIBFT) $(OBJ) $(H_FILES) 
	$(CC) $(FLAGS) $(INCLUDES) $(MAIN_SRC) $(OBJ) $(LIBFT) $(LINKS) -o $(NAME)
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
