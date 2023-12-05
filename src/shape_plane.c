/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:39:10 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/05 19:30:47 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_plane.h"
#include "rt_validations.h"
#include "shading.h"

int	plane_ctor(struct s_plane *plane, t_vec point, t_vec normal, t_color color)
{
	static const struct s_shape_vtable	vtable = {
			(void (*)(struct s_shape *))plane_dtor,
			(double (*)(struct s_shape *, t_ray))plane_intersect_distance,
			(t_color (*)(struct s_shape *, struct s_scene *, t_ray))plane_intersect_color
		};

	shape_ctor(&plane->base, e_PLANE, point, color);
	plane->base.vtptr = &vtable;
	if (!(fleq(fabs(normal.x), 1.0) && fleq(fabs(normal.y), 1.0) && fleq(fabs(normal.z), 1.0)))
		return (1);
	plane->point = point;
	plane->normal = vec_normalize(normal);
	return (0);
}

void	plane_dtor(struct s_plane *plane)
{
	_shape_base_dtor(&plane->base);
}

#include <stdio.h>
double	plane_intersect_distance(struct s_plane *this, t_ray ray)
{
	double	distance;
//	t_point3	p;
	t_point3	q;
	double		a;
	double		d;
	t_point3	impact;

	distance = INFINITY;
	q = ray.origin;
	d = dot_product(this->normal, this->point);			// Not sure about this one... essentially d is distance from origin, afaik
	a = dot_product(q, this->normal) - d;
	impact = vec_add(q, vec_scal_mul(this->normal, (d - dot_product(q, this->normal))));

/* 	if (!feq(dot_product(ray.destination, this->normal), 0))
		result = dot_product(vec_sub(this->point, ray.origin), this->normal) / 
			dot_product(ray.destination, this->normal);
 */
	printf("ray from %f,%f,%f\n", ray.origin.x,ray.origin.y, ray.origin.z);
	if (flessthan(dot_product(ray.destination, this->normal), 0))
	{
		distance = (d - dot_product(ray.origin, this->normal))
			/ dot_product(ray.destination, this->normal);
		impact = vec_add(ray.origin, vec_scal_mul(ray.destination, distance));
		printf("collision with plane at %f,%f,%f distance %f\n", impact.x, impact.y, impact.z, distance);
//		if (flessthan(distance, 0))
//			distance = INFINITY;
	}
	return distance;
}

t_color	plane_intersect_color(struct s_plane *this, struct s_scene *scene, t_ray ray)
{
	t_color		col;
	double		dist;
	t_point3	impact;

//	double d = dot_product(this->point, this->normal);

	col = this->base.col;
	col = apply_ambient(col, scene->ambient);
	dist = plane_intersect_distance(this, ray);	// assume ray.destination is unit vector
	impact = vec_add(ray.origin, vec_scal_mul(ray.destination, dist));
	col = diffuse_shading(scene, (t_ray){impact, this->normal}, col);
	col = specular_lighting(scene, (t_ray){impact, this->normal}, ray, col);
	return col;
}
