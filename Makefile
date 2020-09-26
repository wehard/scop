# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/09/26 15:56:38 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCDIR = src

SRC =	entity.c\
		main.c\
		mesh/mesh_create.c\
		mesh/mesh_destroy.c\
		mesh/mesh_set_vert.c\
		obj_loader.c\
		shader.c\
		mat4.c
		
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

CFLAGS = #-Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I include

UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LDFLAGS = -L libft -lft -lglfw -lGL -lGLEW -lm -lXext -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -L libft -lft -lmlx -lm -framework OpenGL -framework AppKit
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
