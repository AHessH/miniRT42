# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: froxanne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 13:11:24 by froxanne          #+#    #+#              #
#    Updated: 2020/08/21 18:18:49 by froxanne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mymlx.a
PROG_NAME = miniRT

INCLUDES = includes/

SRCS =	srcs/rendering.c \
		srcs/win_control.c \
		srcs/error_exit.c \
		srcs/read_scene_from_file.c \
		srcs/parser.c \
		srcs/parse_res_amb_cam.c \
		srcs/parse_shapes.c \
		srcs/check_scene_errors.c \
		srcs/check_deep_scene_errors.c \
		srcs/check_shape_errors.c \
		srcs/vector_ops1.c \
		srcs/vector_ops2.c \
		srcs/color_ops_1.c \
		srcs/color_ops_2.c \
		srcs/calc_light.c \
		srcs/sphere.c \
		srcs/plane.c \
		srcs/calc_shadow.c \
		srcs/square.c \
		srcs/cylinder.c \
		srcs/disk_cy.c \
		srcs/triangle.c \
		srcs/save_bmp.c \
		srcs/ft_split.c \
		srcs/ft_strchr.c \
		srcs/ft_strdup.c \
		srcs/ft_strjoin.c \
		srcs/ft_strlen.c \
		srcs/ft_strncmp.c \
		srcs/get_next_line.c \
		srcs/ft_atoi.c \
		srcs/ft_atof.c \
		srcs/ft_isdigit.c \
		srcs/ft_is_number.c \
		srcs/emancipator.c \
		srcs/check_colors.c \
		srcs/ft_is_float.c \
		srcs/list_utils.c \
		srcs/ft_memcpy.c \
		srcs/ft_calloc.c \
		srcs/ft_memset.c \
		srcs/ft_strrchr.c

FLAGS = -Wall -Wextra -Werror
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
OSRC = $(SRCS:.c=.o)

.PHONY: all, clean, fclean, re, bonus, comp

all: $(NAME) MLX comp

MLX:
	cd mlx_linux/ && $(MAKE) all

$(NAME): $(OSRC)
	ar rcs $(NAME) $?

%.o: %.c $(INCLUDES)minirt.h
	clang $(FLAGS) -O2 -I$(INCLUDES) -Imlx_linux/ -c $< -o $@

comp:
	clang $(FLAGS) -O2 main.c $(NAME) -I$(INCLUDES) $(LIBS) -o $(PROG_NAME)

bonus: all

clean:
	rm -rf srcs/*.o utils/*.o *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf $(PROG_NAME)
	cd mlx_linux/ && $(MAKE) clean
	
re: fclean all

