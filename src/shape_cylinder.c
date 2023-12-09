/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/09 20:54:55 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"

int	cylinder_ctor(struct s_cylinder *this, t_vec orientation[2],
	double dimensions[2], t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))cylinder_dtor,
		(double (*)(struct s_shape *, t_ray))cylinder_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		cylinder_intersect_color
	};

	shape_ctor(&this->base, e_CYLINDER, orientation[e_LOCATION], color);
	this->base.vtptr = &vtable;
	if (!is_unitvec(orientation[e_AXIS]))
		return (1);
	this->diameter = dimensions[e_DIAMETER];
	this->height = dimensions[e_HEIGHT];
	this->axis = orientation[e_AXIS];
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	double	distance;

	distance = INFINITY;
	(void)this;
	(void)ray;
	return (distance);	// placeholder
}

t_color	cylinder_intersect_color(struct s_cylinder *this,
	struct s_scene *scene, t_ray ray, int bounces)
{
	(void)this;
	(void)ray;
	(void)scene;
	(void)bounces;
	return (this->base.col);	//placeholder
}
