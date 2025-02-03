# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 12:16:30 by ayeganya          #+#    #+#              #
#    Updated: 2024/04/12 14:15:21 by ayeganya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiler CFLAGS
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Header files
H_FILE = push_swap.h

#Source files
M_SRC_FILES = push_swap.c input_reformat.c small_sort.c sort_engine.c utils.c \
			  utils2.c utils3.c utils4.c
B_SRC_FILES = checker.c input_reformat.c input_init.c utils.c checker_utils.c

#Target
NAME  = push_swap
BONUS = checker

all: $(NAME)

$(NAME): $(M_SRC_FILES) $(H_FILE)
	$(CC) $(CFLAGS) $(M_SRC_FILES) -o $@

bonus: $(BONUS) 
	
$(BONUS): $(B_SRC_FILES) $(H_FILE)
	$(CC) $(CFLAGS) -o $(BONUS) $(B_SRC_FILES)

#cleaning targets
clean:

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: all clean fclean re
