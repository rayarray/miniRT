/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 00:36:27 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"

/*
# Cylinder: type identifer | xyz coordinates | vector of axis of cylinder | diameter | height | colors (RGB)
cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
*/

int	cylinder_ctor(struct s_cylinder *this, t_point loc, t_vec axis,
	double *dimensions, t_color color)
{
	static const struct s_shape_vtable	vtable = {
			(void (*)(struct s_shape *this))cylinder_dtor,
			(t_color (*)(struct s_shape *this, struct s_scene *scene, t_ray ray))cylinder_hit_ray
		};

	shape_ctor(&this->base, e_CYLINDER, loc);
	this->base.vtptr = &vtable;
	if (!is_unitvec(axis))
		return (1);
	this->diameter = dimensions[e_DIAMETER];
	this->height = dimensions[e_HEIGHT];
	this->axis = axis;
	this->color = color;
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

t_color	cylinder_hit_ray(struct s_cylinder *this, struct s_scene *scene, t_ray ray)
{
	t_color	color;

	(void)scene;
	(void)ray;
	(void)this;
	color = (t_color){0xFF, 0xFF, 0xFF, 0xFF};	// placeholder
	return (color);
}