# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 16:48:41 by mkulbak           #+#    #+#              #
#    Updated: 2025/07/24 01:28:52 by muhsin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Detect operating system
UNAME_S := $(shell uname -s)

# Common variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -lcurses

ifeq ($(UNAME_S), Darwin)
	CFLAGS += -I/opt/homebrew/include -I/opt/homebrew/opt/readline/include
	LDFLAGS += -L/opt/homebrew/opt/readline/lib
endif

SRC_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC = main.c \
	  lexer/lexer.c \
	  lexer/state.c \
	  lexer/check_operator.c \
	  lexer/lexer_utils.c \
	  lexer/tokenizer.c \
	  lexer/input.c \
	  lexer/expand_dollar.c \
	  parser/parser.c \
	  parser/syntax_check.c \
	  parser/free_segment.c \
	  parser/segment_utils.c \
	  parser/create_segment.c \
	  parser/heredoc.c \
	  parser/heredoc_utils.c \
	  parser/find_cmd.c \
	  signals/signal.c \
	  builtins/echo.c \
	  builtins/cd.c \
	  builtins/pwd.c \
	  builtins/export.c \
	  builtins/unset.c \
	  builtins/env.c \
	  builtins/exit.c \
	  builtins/map_utils.c \
	  builtins/builtins_utils.c \
	  builtins/export_utils.c \
	  builtins/env_manager.c \
	  utils/utils.c \
	  
SRCS = $(addprefix $(SRC_PATH), $(SRC))	
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a


MAKEFLAGS += --silent

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/input
	@mkdir -p $(OBJ_PATH)/lexer
	@mkdir -p $(OBJ_PATH)/parser
	@mkdir -p $(OBJ_PATH)/executor
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/env
	@mkdir -p $(OBJ_PATH)/utils
	@mkdir -p $(OBJ_PATH)/signals

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	echo "🔷 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	echo "✅ Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	echo "✅ Building libft..."
	$(MAKE) -C $(LIBFT_PATH)

clean:
	echo "🧹Cleaning object files..."
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	echo "✅ Cleaning completed!"

fclean: clean
	echo "🧹 Full cleaning is in progress..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	echo "✅ Full cleaning completed!"

re: fclean all

.PHONY: all clean fclean re