/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:01:40 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shape_bonus.h"
#include "parser_bonus.h"
#include "libft.h"

void	shape_ctor(struct s_shape *this, t_elem_type type, t_vec loc,
	t_color col)
{
	static const struct s_shape_vtable	vtable = {_shape_base_dtor, NULL, NULL};

	this->vtptr = &vtable;
	this->type = type;
	this->loc = loc;
	this->col = col;
	this->next = NULL;
}

void	_shape_base_dtor(struct s_shape *this)
{
	(void)this;
}

void	shape_list_clear(struct s_shape **shape)
{
	struct s_shape	*this;

	while (*shape != NULL)
	{
		this = *shape;
		*shape = this->next;
		this->vtptr->shape_dtor(this);
		free(this);
	}
}
