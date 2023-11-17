/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 00:35:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shape.h"
#include "parser.h"
#include "libft.h"

/* // Deprecated or whatever. Replaced these with NULL pointers in shape_ctor
static void	_shape_ctor(struct s_shape *this, char **args)
{
	// Not sure what to do here.
	(void)this;
	(void)args;
	ft_printf("Abstract class constructor _shape_ctor called\n");
	exit(123);
}

static t_color	_hit_ray(struct s_shape *this, struct s_scene *scene, t_ray ray)
{
	(void)this;
	(void)scene;
	(void)ray;
	ft_printf("Abstract class method _hit_ray called\n");
	exit(123);
} */

void	shape_ctor(struct s_shape *this, t_elem_type type, t_point loc)
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
