# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/11/08 18:45:16 by wkorande         ###   ########.fr        #
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

LIBFT_LIGHT_SRC = libft_light/ft_add_vec3.c\
libft_light/ft_atoi.c\
libft_light/ft_bzero.c\
libft_light/ft_cross_vec3.c\
libft_light/ft_deg_to_rad.c\
libft_light/ft_div_vec3.c\
libft_light/ft_dot_vec3.c\
libft_light/ft_get_next_line.c\
libft_light/ft_isdigit.c\
libft_light/ft_len_vec3.c\
libft_light/ft_make_vec2.c\
libft_light/ft_make_vec3.c\
libft_light/ft_memalloc.c\
libft_light/ft_memcpy.c\
libft_light/ft_mul_vec3.c\
libft_light/ft_normalize_vec3.c\
libft_light/ft_nwords.c\
libft_light/ft_parse_vec3.c\
libft_light/ft_putchar.c\
libft_light/ft_putchar_fd.c\
libft_light/ft_putendl.c\
libft_light/ft_putendl_fd.c\
libft_light/ft_putstr.c\
libft_light/ft_putstr_fd.c\
libft_light/ft_strcat.c\
libft_light/ft_strdup.c\
libft_light/ft_strjoin.c\
libft_light/ft_strlen.c\
libft_light/ft_strncmp.c\
libft_light/ft_strncpy.c\
libft_light/ft_strsplit.c\
libft_light/ft_strstr.c\
libft_light/ft_strsub.c\
libft_light/ft_strtod.c\
libft_light/ft_strtok.c\
libft_light/ft_sub_vec3.c


SRCS = $(addprefix $(SRCDIR)/, $(SRC)) $(LODEPNG_SRC) $(LIBFT_LIGHT_SRC)

CFLAGS = #-Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I include -I lib/include

UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LDFLAGS =  -lglfw -lGL -lGLEW -lm -lXext -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS =  -L lib -lglfw3 -L lib -lGLEW -lm -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	endif

CC = clang

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LDFLAGS) -o $(NAME)


debug:
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	#@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	# @make fclean -C libft

re: fclean all

.PHONY: all libftdebug clean fclean re run debug
