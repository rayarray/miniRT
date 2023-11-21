# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/12/12 11:55:02 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

PARSER		=	ambient_lighting.c camera.c parse_file_reader.c get_next_line.c \
				get_next_line_utils.c light.c minirt.c parse_conversions.c \
				parse_scene.c parse_shape.c parse_utilities.c rt_math.c \
				rt_split.c rt_validations.c scene.c shape.c shape_cylinder.c \
				shape_plane.c shape_sphere.c tracer.c vector.c hooks.c color.c \
				shading.c
# TODO should include headers here so that program recompiles if only header file has changed

SRC			=	$(PARSER)

LIBS		=	libft

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include libft MLX42/include/MLX42

OBJ			=	$(foreach o, $(SRC:.c=.o),$(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBS),-I $(l) -L $(l) -l$(l:lib%=%))
LIBARC		=	$(foreach l, $(LIBS),$(l)/$(l).a)
INCLUDE		=	$(foreach i, $(INCDIR),-I $(i)) $(foreach l, $(LIBS),-I $l)

CFLAGS		=	-Wall -Wextra -Werror
SFLAGS		=	-fsanitize:address -g

CC 			=	cc

# =============== MLX42 ==============
# libmlx42.a: MLX42/build/libmlx42.a
# MLX42.h	: MLX42/include/MLX42/MLX42.h
MLX42		=	-framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
# ====================================

all: $(NAME)

$(NAME): $(OBJ) $(LIBARC)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBINC) $(MLX42) -o $@ $(OBJ)

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $(SRCDIR)/$(notdir $(@:.o=.c))

$(LIBARC): %:
	$(MAKE) -j$(NPROCS) -C $(basename $(notdir $@))

clean:
	@$(foreach l, $(LIBS),$(MAKE) -C $(l) clean;)
	@rm -f $(foreach o, $(OBJ),$(o))
	@if [ -d $(OBJDIR) ]; then rmdir $(OBJDIR); fi

fclean: clean
	@$(foreach l, $(LIBS),$(MAKE) -C $(l) fclean;)
	@if [ -f $(NAME) ]; then /bin/rm $(NAME); fi

re: fclean all

.PHONY: bonus