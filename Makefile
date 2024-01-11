# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2024/01/11 18:00:55 by tsankola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

# include headers here so that program recompiles if a header file changes
_HDR		=	ambient_lighting_bonus.h camera_bonus.h color_bonus.h \
				get_next_line_bonus.h light_bonus.h minirt_bonus.h \
				parser_bonus.h rt_conversions_bonus.h rt_math_bonus.h \
				rt_typedef_bonus.h 	rt_validations_bonus.h scene_bonus.h \
				shading_bonus.h shape_cylinder_bonus.h shape_bonus.h \
				shape_plane_bonus.h shape_sphere_bonus.h tracer_bonus.h \
				vector_bonus.h render_bonus.h shape_cone_bonus.h

SRC			=	ambient_lighting_bonus.c camera_bonus.c \
				parse_file_reader_bonus.c get_next_line_bonus.c \
				get_next_line_utils_bonus.c light_bonus.c minirt_bonus.c \
				parse_conversions_bonus.c parse_scene_bonus.c \
				parse_shape_bonus.c parse_utilities_bonus.c rt_math_bonus.c \
				rt_split_bonus.c scene_bonus.c shape_bonus.c \
				shape_cylinder_bonus.c shape_plane_bonus.c \
				shape_sphere_bonus.c tracer_bonus.c vector_bonus.c \
				hooks_bonus.c color_bonus.c shading_bonus.c \
				value_checks_bonus.c form_checks_bonus.c render_bonus.c \
				rt_math_cylinder_bonus.c vector2_bonus.c shape_common_bonus.c \
				rt_math_comparisons_bonus.c shape_cone_bonus.c \
				shape_cone_utils_bonus.c

LIBS		=	libft.a libftprintf.a
LIBDIRS		=	libft libft/libftprintf

LIB		=

LIBFTINC	=	libft
LIBFTARC	=	$(LIBFTINC)/libft.a

PRINTFINC	=	libft/libftprintf
PRINTFARC	=	libft/libftprintf/libftprintf.a

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include libft libft/libftprintf MLX42/include/MLX42

HDR			=	$(foreach h, $(_HDR), include/$(h))
OBJ			=	$(foreach o, $(SRC:.c=.o), $(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBDIRS), -L$(l))
LIBARC		=	$(foreach l, $(LIBS), -l$(l:lib%.a=%))
INCLUDE		=	$(foreach i, $(INCDIR),-I $(i))

CFLAGS		=	-Wall -Wextra -Werror
SFLAGS		=	-fsanitize:address -g

CC 			=	cc

OS := $(shell uname)

# =============== MLX42 ==============
# libmlx42.a: MLX42/build/libmlx42.a
# MLX42.h	: MLX42/include/MLX42/MLX42.h
ifeq ($(OS),Darwin) # Assume Mac OS X
	MLX42		=	-framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif
ifeq ($(OS),Linux)	# Assume WSL and prebuilt MLX42. Haven't tested with pure Linux yet
	MLX42		=	-LMLX42/build -lmlx42 -ldl -lglfw -pthread -lm
endif
# ====================================

all: $(NAME)

$(NAME): $(OBJ) $(LIBFTARC) $(PRINTFARC) $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJ) $(LIBINC) $(LIBARC) $(MLX42)

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(HDR)
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $(SRCDIR)/$(notdir $(@:.o=.c)) #$(MLX42)

$(LIBFTARC): %:
	$(MAKE) -j4 -C $(LIBFTINC)

$(PRINTFARC): %:
	$(MAKE) -j4 -C $(PRINTFINC)

clean:
	$(foreach l, $(LIBDIRS),$(MAKE) -C $(l) clean;)
	$(foreach o, $(OBJ),rm -f $(o);)
	rmdir $(OBJDIR) || true

fclean: clean
	$(foreach l, $(LIBDIRS),$(MAKE) -C $(l) fclean;)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: bonus