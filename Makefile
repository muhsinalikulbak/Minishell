# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 16:48:41 by mkulbak           #+#    #+#              #
#    Updated: 2025/06/15 23:57:10 by kayraakbas       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compiler and compilation flags
CC = cc
CFLAGS = 
LDFLAGS = -lreadline

# Build files and directories
SRC_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

# Source files (manually listed)
SRC = main.c \
      input/input_handler.c \
	  lexer/lexer.c \
	  lexer/token_utils.c \
	  parser/parser.c \
	  parser/parser_utils.c \
	  
# Object files generation
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# Include directories
INC = -I $(INC_PATH) -I $(LIBFT_PATH)

# Libft configuration
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a


MAKEFLAGS += --silent

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Objects directory rule - creates all necessary subdirectories
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

# Objects compilation rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	echo "🔷 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Program linking rule
$(NAME): $(OBJS)
	echo "✅ Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(LDFLAGS)

# Libft compilation rule
$(LIBFT):
	echo "✅ Building libft..."
	$(MAKE) -C $(LIBFT_PATH)

# Clean object files
clean:
	echo "🧹Cleaning object files..."
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	echo "✅ Cleaning completed!"

# Clean everything
fclean: clean
	echo "🧹 Full cleaning is in progress..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	echo "✅ Full cleaning completed!"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re