
NAME = libmlx.a

CC = gcc
FLAGS = -O2

INCLUDES = -I$(HEADERS_DIR)

SRC_DIR = src/
SRC_LIST =	mlx_new_window.m \
	    	mlx_init_loop.m \
	    	mlx_new_image.m \
	    	mlx_xpm.c \
	    	mlx_int_str_to_wordtab.c \
	    	mlx_shaders.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST1 = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ_LIST = $(patsubst %.m, %.o, $(OBJ_LIST1))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

HEADERS_LIST = mlx.h
HEADERS_DIR = ./inc/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

# COLORS

GRN = \033[0;32m
RED = \033[0;31m
YEL = \033[1;33m
END = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GRN)library created$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GRN).$(END)\c"

$(OBJ_DIR)%.o: $(SRC_DIR)%.m
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GRN).$(END)\c"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GRN)$(OBJ_DIR) created$(END)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) deleted$(END)"
	@echo "$(NAME): $(RED)*.o files deleted$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) deleted$(END)"

re: clean all
