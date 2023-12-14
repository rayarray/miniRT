/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/14 13:02:06 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shape.h"
#include "parser.h"
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
	(void)this; // Nothing to free here
}

void	shape_dtor(struct s_shape *this)
{
	this->vtptr->shape_dtor(this);
}

double	intersect_distance(struct s_shape *this, t_ray ray)
{
	return (this->vtptr->intersect_distance(this, ray));
}

t_color	intersect_color(struct s_shape *this, struct s_scene *scene, t_ray ray,
			int bounces)
{
	return (this->vtptr->intersect_color(this, scene, ray, bounces - 1));
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
