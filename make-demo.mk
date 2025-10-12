# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make-demo.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:36:56 by fpaglia           #+#    #+#              #
#    Updated: 2025/10/11 00:13:59 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -g3
INCLUDES = -Iinclude -Ilibs/libft 
LINKS = -lreadline
#DEMO creation
DEMO_SRC = $(wildcard demo/source/*.c)
DEMO_BIN = $(patsubst demo/source/%,demo/bin/%,$(DEMO_SRC:.c=.out))

LIBFT := libs/libft/libft.a
MINI := build/libmini.a
all: $(DEMO_BIN)

demo/bin/%.out:  demo/source/%.c $(MINI) $(LIBFT)
	@ mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) $^ $(LINKS) -o $@ 

.PHONY: all
