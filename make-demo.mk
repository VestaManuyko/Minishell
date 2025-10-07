# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make-demo.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:36:56 by fpaglia           #+#    #+#              #
#    Updated: 2025/10/07 17:25:30 by vmanuyko         ###   ########.fr        #
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

LIBFT = libs/libft/libft.a
all: $(DEMO_BIN)

demo/bin/%.out:  demo/source/%.c $(OBJ) $(LIBFT)
	@ mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) $^ -lreadline -o $@ 

.PHONY: all democlean demore


democlean: 
	-rm  -rf $(DEMO_BIN)

demore: democlean demo
