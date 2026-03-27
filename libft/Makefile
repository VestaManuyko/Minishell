# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 14:40:11 by fpaglia           #+#    #+#              #
#    Updated: 2025/11/03 10:49:31 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
#FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
C_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_toupper.c ft_tolower.c \
		  ft_strchr.c ft_strrchr.c ft_strncmp.c \
		  ft_strlen.c ft_atoi.c \
		  ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memmove.c \
		  ft_memcmp.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c \
		  ft_calloc.c ft_strdup.c ft_strncpy.c \
		  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		  ft_itoa.c ft_lltoa_base.c \
		  ft_strmapi.c ft_striteri.c \
		  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		  ft_isspace.c ft_quicksort.c ft_swap.c \
		  get_next_line.c

C_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
		  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c 

H_FILES = libft.h get_next_line.h

OBJS = $(C_FILES:.c=.o)
O_BONUS = $(C_BONUS:.c=.o)

NAME = libft.a

$(NAME): $(OBJS)
	@ar rcs $@ $^
%.o: %.c $(H_FILES)
	@$(CC) $(FLAGS) -I. -c $< -o $@

.PHONY: all clean fclean re gettest norm bonus objslist

all: $(NAME)
clean:
	@-rm -rf $(OBJS) $(O_BONUS) 
fclean: clean
	@-rm -rf $(NAME) *.out
re: fclean all

norm:
	@norminette $(C_FILES) $(H_FILES) $(C_BONUS)

objslist:
	@echo $(addprefix libft/,$(OBJS))

#gettests:
#	cp -av ~/gitHubExchange/commoncore/libft/make_test.mk .

bonus: $(NAME) $(O_BONUS) $(H_FILES) 
	@ update=false; \
	for afile in $(O_BONUS); do \
		if [ $$afile -nt $(NAME) ]; then \
			update=true; \
			break; \
		fi; \
	done; \
	if ! $$update; then \
		echo "make: '$(NAME)' is up to date."; \
	else \
		echo "ar rcs $(NAME) $(O_BONUS) $(H_FILES)"; \
		ar rcs $(NAME) $(O_BONUS) $(H_FILES); \
	fi
