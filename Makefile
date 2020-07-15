# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 13:56:52 by esnowpea          #+#    #+#              #
#    Updated: 2020/07/15 14:32:19 by esnowpea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
FLAGS = -O2 -Wall -Werror -Wextra
LIB_FLAGS = -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(LIBMLX_HEADERS)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)inc/

LIBMLX = $(LIBFT_DIR)libmlx.a
LIBMLX_DIR = ./minilibx_macos/
LIBMLX_HEADERS = $(LIBFT_DIR)

HEADERS_LIST = $(NAME).h
HEADERS_DIR = ./inc/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = src/
SRC_LIST =	main.c \
			init.c \
			draw_win.c \
			event_handler.c \
			mandelbrot.c \
			julia.c \
			mouse_hook.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GRN = \033[0;32m
RED = \033[0;31m
YEL = \033[1;33m
END = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIB_FLAGS) $(INCLUDES) $(OBJ) -o $@
	@echo "\n$(NAME): $(GRN)*.o files created$(END)"
	@echo "$(NAME): $(GRN)$(NAME) created$(END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GRN)$(OBJ_DIR) created$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GRN).$(END)\c"

$(LIBFT):
	@echo "$(NAME): $(GRN)Creating $(LIBFT)...$(END)"
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	@echo "$(NAME): $(GRN)Creating $(LIBMLX)...$(END)"
	@$(MAKE) -C $(LIBMLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIBMLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) deleted$(END)"
	@echo "$(NAME): $(RED)*.o files deleted$(END)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(NAME): $(RED)$(LIBFT) deleted$(END)"
	@$(MAKE) -C $(LIBMLX_DIR) fclean
	@echo "$(NAME): $(RED)$(LIBMLX) deleted$(END)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) deleted$(END)"

re: fclean all
