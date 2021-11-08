# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/11/08 16:20:51 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCDIR = src

SRC =	entity.c\
		main.c\
		mesh/mesh_create.c\
		mesh/mesh_destroy.c\
		mesh/mesh_set_vert.c\
		mesh/mesh_gen_uvs.c\
		mesh/mesh_center.c\
		obj_loader.c\
		shader/shader_create.c\
		shader/shader_destroy.c\
		shader/shader_set.c\
		mat4/mat4_init.c\
		mat4/mat4_lookat.c\
		mat4/mat4_mul.c\
		mat4/mat4_rotate.c\
		mat4/mat4_scale.c\
		mat4/mat4_trs.c\
		mat4/mat4_identity.c\
		mat4/mat4_perspective.c\
		mat4/mat4_translate.c\
		camera.c\
		tex.c\
		input.c\
		utils.c\
		init.c\

LODEPNG_SRC = lib/lodepng/lodepng.c


SRCS = $(addprefix $(SRCDIR)/, $(SRC)) $(LODEPNG_SRC)

CFLAGS = #-Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I include -I lib/include

UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LDFLAGS = -L libft -lft -lglfw -lGL -lGLEW -lm -lXext -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -L libft -lft -L lib -lglfw3 -L lib -lGLEW -lm -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	endif

CC = clang

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LDFLAGS) -o $(NAME)

libftdebug:
	@make debug -C libft

debug:
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	#@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	# @make fclean -C libft

re: fclean all

.PHONY: all libftdebug clean fclean re run debug
