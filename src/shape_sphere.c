/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:16:05 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/19 17:57:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_sphere.h"
#include "rt_typedef.h"
#include "math.h"
#include "rt_math.h"

int	sphere_ctor(struct s_sphere *this, t_vec loc, double diameter, t_color color)
{
	static const struct s_shape_vtable	sphere_vtable = {
			(void (*)(struct s_shape *this))sphere_dtor,
			(double (*)(struct s_shape *this, t_ray ray))sphere_intersect_distance
		};

	shape_ctor(&this->base, e_SPHERE, loc, color);
	this->base.vtptr = &sphere_vtable;
	this->diameter = diameter;
	return (0);
}

void	sphere_dtor(struct s_sphere *this)
{
	_shape_base_dtor(&this->base);
}

t_color	sphere_hit_ray(struct s_sphere *this, struct s_scene *scene, t_ray ray)
{
	t_color	color;

	(void)scene;
	(void)ray;
	(void)this;
	color = this->base.col;
	return (color);
}

#include <stdio.h>
double	sphere_intersect_distance(struct s_sphere *s, t_ray ray)
{
	t_vec	l;	// vector between origin and sphere
	double	t;	// distance from origin to a line s that is perpendicular between destination line and l
	double	d;	// distance between s.loc and the line s above
	double	u;	// distance between line s and impact point
	double	impact_dist;

	l = vec_sub(s->base.loc, ray.origin);
	t = dot_product(l, ray.destination);
	if (t < 0)							
		return INFINITY;
	d = sqrt(pow(vec_length(l), 2) - pow(t, 2));
	if (d < 0 || d > s->diameter / 2)		// second comparison checks if the intersection is outside the radius
		return INFINITY;
	u = sqrt(pow(s->diameter / 2, 2) - pow(d, 2));
	if (t - u < t + u)
		impact_dist = t - u;
	else
		impact_dist = t + u;
//	t_vec	impact_point = vec_scal_mul(ray.destination, impact_dist);
//	printf("sphere at %f %f %f diameter %f\n", s->base.loc.x, s->base.loc.y, s->base.loc.z, s->diameter);
//	printf("impact %f %f %f!\n", impact_point.x, impact_point.y, impact_point.z);
	return (impact_dist);
}
