# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/10/14 20:30:39 by tsankola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT_parser

PARSER		=	get_next_line.c get_next_line_utils.c line_parser.c \
				parser_utilities.c scene_reader.c rt_split.c rt_conversions.c

SRC			=	$(PARSER)

LIBS		=	libft

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include libft

OBJ			=	$(foreach o, $(SRC:.c=.o), $(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBS), -I $(l) -L $(l) -l$(l:lib%=%))
LIBARC		=	$(foreach l, $(LIBS), $(l)/$(l).a)
INCLUDE		=	$(foreach i, $(INCDIR),-I $(i))

CFLAGS		=	-Wall -Wextra -Werror
SFLAGS		=	-fsanitize:address -g

CC 			=	cc

all: $(NAME)

$(NAME): $(OBJ) $(LIBARC)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBINC) -o $@ $(OBJ)

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