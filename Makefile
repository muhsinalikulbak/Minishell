# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 16:48:41 by mkulbak           #+#    #+#              #
#    Updated: 2025/06/26 20:56:14 by omakbas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -g
LDFLAGS = -lreadline

SRC_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC = main.c \
	  lexer/lexer.c \
	  lexer/state.c \
	  lexer/state_utils.c \
	  lexer/token_utils.c \
	  lexer/input.c \
	  parser/parser.c \
	  parser/parser_utils.c \
	  parser/syntax_check.c \
	  signals/signal.c \
	  executor/builtins.c \
	  executor/map_utils.c \
	  
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