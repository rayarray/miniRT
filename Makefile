# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/11/17 19:39:01 by tsankola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

PARSER		=	ambient_lighting.c camera.c element_parser.c get_next_line.c \
				get_next_line_utils.c light.c line_parser.c minirt.c \
				parser_utilities.c rt_conversions.c rt_math.c rt_split.c \
				rt_validations.c scene.c scene_parsing.c scene_reader.c \
				shape.c shape_sphere.c vector.c tracer.c

SRC			=	$(PARSER)

LIBS		=	libft

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include libft MLX42/include/MLX42

OBJ			=	$(foreach o, $(SRC:.c=.o), $(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBS), -I $(l) -L $(l) -l$(l:lib%=%))
LIBARC		=	$(foreach l, $(LIBS), $(l)/$(l).a)
INCLUDE		=	$(foreach i, $(INCDIR),-I $(i))

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
	$(MAKE) -j4 -C $(basename $(notdir $@))

clean:
	$(foreach l, $(LIBS),$(MAKE) -C $(l) clean;)
	$(foreach o, $(OBJ),rm $(o);)
	rmdir $(OBJDIR)

fclean: clean
	$(foreach l, $(LIBS),$(MAKE) -C $(l) fclean;)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: bonus