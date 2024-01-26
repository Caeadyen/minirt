# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrings <hrings@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/19 14:17:49 by hrings            #+#    #+#              #
#    Updated: 2024/01/27 00:18:00 by hrings           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = miniRT

CC = gcc

LIBMLX	:= ./MLX42

# MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
# MINILIBX_DIRECTORY = ./minilibx-linux/
MLX_INC	= -I $(LIBMLX)/include
MLX_LNK	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -fsanitize=address
LIBRARIES = $(FT_LNK) $(MLX_LNK)
INCLUDES = $(MLX_INC) $(FT_INC)

OBJDIR = build/
HEADER = ./header
SRCDIR = src/

LIBFT = $(LIBFT_DIRECTORY)/libft.a
LIBFT_DIRECTORY = ./libft
FT_INC	= -I ./libft/
FT_LNK	= ./libft/libft.a



SRCS := main.c draw.c raytracing.c cleanup.c lst_obj.c utilities.c \
		vector_3d.c make_obj.c color.c cylinder.c plane.c

OBJECTS := $(SRCS:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJDIR), $(OBJECTS))


GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_PREFIXED) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJECTS_PREFIXED) $(LIBRARIES) -I$(HEADER) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"


$(OBJECTS_PREFIXED): build/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c  $< -o $@ -I$(HEADER) $(INCLUDES)
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) all -sC $(LIBFT_DIRECTORY)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
#	@cd ./$(LIBFT_DIRECTORY) && make clean
#	@cd ./$(MINILIBX_DIRECTORY) &&  make clean
	@rm -rf $(OBJDIR)
	@echo "$(NAME): $(RED)object files and directory were deleted$(RESET)"

fclean: clean
#	@cd ./$(LIBFT_DIRECTORY) && make fclean
#	@cd ./$(MINILIBX_DIRECTORY) &&  make clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Libaries were deleted$(RESET)"

re: fclean all
