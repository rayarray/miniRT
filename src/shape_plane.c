/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:39:10 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/12 10:25:24 by tsankola         ###   ########.fr       */
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
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		plane_intersect_color
	};

	shape_ctor(&plane->base, e_PLANE, point, color);
	plane->base.vtptr = &vtable;
	if (!is_direction_vector(normal))
		return (1);
	plane->point = point;
	plane->normal = vec_normalize(normal);
	return (0);
}

void	plane_dtor(struct s_plane *plane)
{
	_shape_base_dtor(&plane->base);
}

double	plane_intersect_distance(struct s_plane *this, t_ray ray)
{
	double	distance;
	double	denom;

	distance = -1;
	denom = dot_product(this->normal, ray.destination);
	if (!feq(denom, 0))
		distance = dot_product(vec_sub(this->point, ray.origin), this->normal)
			/ denom;
	if (flessthan(distance, 0))
		distance = INFINITY;
	return (distance);
}

t_color	plane_intersect_color(struct s_plane *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	t_color		col;
	double		dist;
	t_point3	impact;
	t_vec		normal_to_ray;

	(void)bounces;		// ...
	col = this->base.col;
	dist = plane_intersect_distance(this, ray);
	col = apply_ambient(col, scene->ambient);
	if (dist != INFINITY)
	{
		impact = vec_add(ray.origin, vec_scal_mul(ray.destination, dist));
		if (fgreaterthan(dot_product(ray.destination, this->normal), 0))
			normal_to_ray = vec_neg(this->normal);
		else
			normal_to_ray = this->normal;
		col = diffuse_shading(scene, (t_ray){impact, normal_to_ray}, col);
		col = specular_lighting(scene, (t_ray){impact, normal_to_ray}, ray, col);
		col = specular_reflection(scene, (t_ray){impact, normal_to_ray}, ray, col, bounces);
	}
	return (col);
}
