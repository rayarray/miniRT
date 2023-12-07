/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/07 19:03:53 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"

/*
# Cylinder: type identifer | xyz coordinates | vector of axis of cylinder | diameter | height | colors (RGB)
cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
*/

int	cylinder_ctor(struct s_cylinder *this, t_point3 loc, t_vec axis,
	double *dimensions, t_color color)
{
	static const struct s_shape_vtable	vtable = {
			(void (*)(struct s_shape *))cylinder_dtor,
			(double (*)(struct s_shape *, t_ray))cylinder_intersect_distance,
			(t_color (*)(struct s_shape *, struct s_scene *, t_ray))cylinder_intersect_color
		};

	shape_ctor(&this->base, e_CYLINDER, loc, color);
	this->base.vtptr = &vtable;
	if (!is_unitvec(axis))
		return (1);
	this->diameter = dimensions[e_DIAMETER];
	this->height = dimensions[e_HEIGHT];
	this->axis = axis;
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	double	distance;

	distance = -1;
	double denom = dot_product(this->normal, ray.destination);
	if (!feq(denom, 0))
		distance = dot_product(vec_sub(this->point, ray.origin), this->normal) / denom;
	if (flessthan(distance, 0))
		distance = INFINITY;
	return distance;

}

t_color	cylinder_intersect_color(struct s_cylinder *this, struct s_scene *scene, t_ray ray)
{
	(void)this;
	(void)ray;
	(void)scene;
	return this->base.col;	//placeholder
}
