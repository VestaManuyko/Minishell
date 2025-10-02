# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make-demo.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:36:56 by fpaglia           #+#    #+#              #
#    Updated: 2025/10/02 12:52:30 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -g3
INCLUDES = -Iinclude -Ilibs/libft

OBJ = $(wildcard source/*/*.c)
#DEMO creation
DEMO_SRC = $(wildcard demo/source/*.c)
DEMO_BIN = $(patsubst demo/source/%,demo/bin/%,$(DEMO_SRC:.c=.out))

all: $(DEMO_BIN)

demo/bin/%.out:  $(OBJ) $(LIBFT) demo/source/%.c
	@ mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ 

.PHONY: all democlean demore


democlean: 
	-rm  -rf $(DEMO_BIN)

demore: democlean demo
