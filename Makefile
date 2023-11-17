# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/12/12 11:49:47 by rleskine         ###   ########.fr        #
=======
#    Updated: 2023/11/17 19:39:01 by tsankola         ###   ########.fr        #
>>>>>>> fc89113... Thinking about redoing the parser. Current implementation is too overengineered and cumbersome. There's no need to first do the base elements and then do the actual allocating. Arguments can be checked while parsing the input file and elements can be saved in a linked list. Thus it should be easier to create the scene. Iterating through the elements might be a bit tougher but I don't think that there is need to do backwards traversal in the list.
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