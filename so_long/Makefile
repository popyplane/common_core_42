# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 10:34:24 by bvieilhe          #+#    #+#              #
#    Updated: 2023/07/26 10:19:21 by bvieilhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

SRCS		=	display.c \
				error.c \
				free.c \
				ft_split.c \
				hooks.c \
				main.c \
				map.c \
				map2.c \
				mem.c \
				print.c \
				strings.c \
				texture.c \
				utils.c

OBJS 		=	${SRCS:.c=.o}

RM			=	rm
RMFLAG		=	-f

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3

UNAME		=	$(shell uname)

# MLX42 (github.com/codam-coding-college/MLX42), built from vendored source via
# CMake. Replaced the original minilibx-linux dependency, which is Linux/X11
# only and can't run on this machine at all; MLX42 is cross-platform and the
# same library already used for this repo's cub3d.
ifeq ($(UNAME), Linux)
	INCLUDES	=	-Imlx/include -I.
	MLX_FLAGS	=	-Lmlx/build -lmlx42 -lglfw -lGL -lm -ldl -lpthread
else ifeq ($(UNAME), Darwin)
	GLFW_PREFIX	=	$(shell brew --prefix glfw 2>/dev/null)
	INCLUDES	=	-Imlx/include -I. -I$(GLFW_PREFIX)/include
	MLX_FLAGS	=	-Lmlx/build -lmlx42 -L$(GLFW_PREFIX)/lib -lglfw \
					-framework Cocoa -framework OpenGL -framework IOKit -lm
endif

MLX_DIR		=	./mlx
MLX_LIB		=	$(MLX_DIR)/build/libmlx42.a

%.o: %.c
	$(CC) $(CFLAGS) ${INCLUDES} -c $< -o $@

all:			$(MLX_LIB) ${NAME}

$(MLX_LIB):
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) -DGLFW_FETCH=OFF
	@cmake --build $(MLX_DIR)/build -j4

${NAME}:		$(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean:
	${RM} ${RMFLAG} ${OBJS}

fclean:			clean
	${RM} ${RMFLAG} ${NAME}
	if [ -d "$(MLX_DIR)/build" ]; then rm -rf $(MLX_DIR)/build; fi

re:				fclean all

.PHONY: all clean fclean re
