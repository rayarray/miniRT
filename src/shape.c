/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 23:54:37 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shape.h"
#include "parser.h"
#include "libft.h"

void	shape_ctor(struct s_shape *this, t_elem_type type, t_point3 loc)
{
	static const struct s_shape_vtable	vtable = {_shape_base_dtor, NULL};

	this->vtptr = &vtable;
	this->type = type;
	this->loc = loc;
	this->next = NULL;
}

void	_shape_base_dtor(struct s_shape *this)
{
	(void)this; // Nothing to free here
}

void	shape_dtor(struct s_shape *this)
{
	this->vtptr->shape_dtor(this);
}

t_color	hit_ray(struct s_shape *this, struct s_scene *scene, t_ray ray)
{
	return (this->vtptr->hit_ray(this, scene, ray));
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
