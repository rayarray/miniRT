# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/12/12 11:49:47 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT_parser

PARSER		=	get_next_line.c get_next_line_utils.c line_parser.c \
				parser_utilities.c scene_reader.c rt_split.c rt_conversions.c \
				rt_math.c rt_validations.c

SRC			=	$(PARSER)

LIBS		=	libft

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include MLX42/include/MLX42
LIBFLG		=	-lm

OBJ			=	$(foreach o, $(SRC:.c=.o),$(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBS),-I $(l) -L $(l) -l$(l:lib%=%))
LIBARC		=	$(foreach l, $(LIBS),$(l)/$(l).a)
INCLUDE		=	$(foreach i, $(INCDIR),-I $(i)) $(foreach l, $(LIBS),-I $l)

CFLAGS		=	-Wall -Wextra -Werror
SFLAGS		=	-fsanitize:address -g

CC 			=	cc

# == Determine OS and CPU core count =
OS := $(shell uname)

ifeq ($(OS),Linux)
  NPROCS:=$(shell grep -c ^processor /proc/cpuinfo)
endif
ifeq ($(OS),Darwin) # Assume Mac OS X
  NPROCS:=$(shell sysctl hw.ncpu | grep -o '[0-9]\+')
endif
# ====================================

# =============== MLX42 ==============
# libmlx42.a: MLX42/build/libmlx42.a
# MLX42.h	: MLX42/include/MLX42/MLX42.h
MLX42		=	-framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
# ====================================

all: $(NAME)

$(NAME): $(OBJ) $(LIBARC)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLG) $(LIBINC) $(MLX42) -o $@ $(OBJ)

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