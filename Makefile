# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 16:48:41 by mkulbak           #+#    #+#              #
#    Updated: 2025/06/12 14:59:29 by kayraakbas       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I include
LDFLAGS = -lreadline

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a
# INCLUDES += -I$(LIBFT_DIR)

all: $(NAME)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)
    #if using libft: $(LIBFT)

# If using libft, uncomment this rule
# $(LIBFT):
#	@echo "Building libft..."
#	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
    #if using libft: @$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "Removing executable $(NAME)..."
	@rm -f $(NAME)
    # if using libft: @$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re