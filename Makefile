# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/10/09 16:57:30 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

SRC			=	minirt.c minirt2.c

LIBS		=	libft

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include

OBJ			=	$(foreach o, $(SRC:.c=.o), $(OBJDIR)/$(o))
LIBINC		=	$(foreach l, $(LIBS), -I $(l) -L $(l) -l$(l:lib%=%))
LIBARC		=	$(foreach l, $(LIBS), $(l)/$(l).a)
INCLUDE		=	-I $(INCDIR) $(foreach l, $(LIBS), -I $l)

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