# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/12/12 11:12:59 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

# include headers here so that program recompiles if a header file changes
_HDR			=	ambient_lighting.h camera.h color.h get_next_line.h light.h \
				minirt.h parser.h rt_conversions.h rt_math.h rt_typedef.h \
				rt_validations.h scene.h shading.h shape_cylinder.h shape.h \
				shape_plane.h shape_sphere.h tracer.h vector.h render.h

SRC			=	ambient_lighting.c camera.c parse_file_reader.c get_next_line.c \
				get_next_line_utils.c light.c minirt.c parse_conversions.c \
				parse_scene.c parse_shape.c parse_utilities.c rt_math.c \
				rt_split.c scene.c shape.c shape_cylinder.c \
				shape_plane.c shape_sphere.c tracer.c vector.c hooks.c color.c \
				shading.c value_checks.c form_checks.c render.c

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