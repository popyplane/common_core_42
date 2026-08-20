# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:45:26 by codespace         #+#    #+#              #
#    Updated: 2024/06/21 14:58:28 by baptistevie      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME	=		cub3D

# SRCS_FILES	=	get_map.c \
# 				get_map_utils.c \
# 				error.c \
# 				main.c

# INC_FILES	= cub3d.h

# SRCS	=	$(addprefix src/, $(SRCS_FILES))

# INCS	=	$(addprefix inc/, $(INC_FILES))

# CC		=	clang

# CFLAGS	=	-Wall -Wextra -Werror -I./inc -g3

# INCLUDES	= -I. -Imlx/.

# LIB		= -Lmlx -lmlx -lXext -lX11 -Llibft -lft -lm

# OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)

# OBJS	=		$(addprefix objs/, $(OBJS_FILES))

# DEP		=		$(OBJS:%.o=%.d)

# all		:		$(NAME)

# $(NAME)	:	$(OBJS)
# 	make -C libft
# 	make -C mlx
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIB)

# clean	:
# 	make -C libft fclean
# 	make -C mlx clean
# 	rm -rf $(OBJS) $(DEP)
# 	rm -rf objs/

# fclean	:	clean
# 	rm -rf $(NAME)

# re		:	fclean all

# objs/%.o	: src/%.c $(INCS)
# 	mkdir -p objs
# 	$(CC) $(CFLAGS) -MMD -o $@ -c $<

# .PHONY: all clean fclean re

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

RM = rm
RMFLAG = -f

UNAME = $(shell uname)

# MLX42 (github.com/codam-coding-college/MLX42), built from vendored source
# via CMake. Replaced the classic X11/Cocoa minilibx fork this project
# started with: that one never actually presented frames to the screen on
# modern macOS (its render loop called glFlush() instead of swapping the
# compositor buffer), and MLX42 is actively maintained specifically to
# avoid this class of platform bug.
ifeq ($(UNAME), Linux)
	INCLUDES = -Imlx/include -Iinc
	MLX_FLAGS = -Lmlx/build -lmlx42 -lglfw -lGL -lm -ldl -lpthread
else ifeq ($(UNAME), Darwin)
	GLFW_PREFIX = $(shell brew --prefix glfw 2>/dev/null)
	INCLUDES = -Imlx/include -Iinc -I$(GLFW_PREFIX)/include
	MLX_FLAGS = -Lmlx/build -lmlx42 -L$(GLFW_PREFIX)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -lm
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -Llibft -lft

SRCS_FILES	=	display_2d.c \
				error.c \
				get_map_utils.c \
				get_map.c \
				hooks.c \
				img.c \
				init.c \
				main.c \
				player.c \
				raycast.c \
				render.c

INC_FILES	= cub3d.h

SRCS	=	$(addprefix src/, $(SRCS_FILES))
INCS	=	$(addprefix inc/, $(INC_FILES))

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(MLX_LIB):
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) -DGLFW_FETCH=OFF
	@cmake --build $(MLX_DIR)/build -j4

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)
	if [ -d "$(MLX_DIR)/build" ]; then rm -rf $(MLX_DIR)/build; fi
	if [ -d "./libft" ]; then make -C $(LIBFT_DIR) fclean; fi

re: fclean all

.PHONY: all clean run fclean re 