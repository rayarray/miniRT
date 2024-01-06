/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:16:05 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/06 16:36:24 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_sphere.h"
#include "rt_typedef.h"
#include "math.h"
#include "rt_math.h"
#include "color.h"
#include "shading.h"

int	sphere_ctor(struct s_sphere *s, t_vec loc, double diameter, t_color color)
{
	static const struct s_shape_vtable	sphere_vtable = {
		(void (*)(struct s_shape *))sphere_dtor,
		(double (*)(struct s_shape *, t_ray))sphere_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		sphere_intersect_color
	};

	shape_ctor(&s->base, e_SPHERE, loc, color);
	s->base.vtptr = &sphere_vtable;
	s->diameter = diameter;
	return (0);
}

void	sphere_dtor(struct s_sphere *s)
{
	_shape_base_dtor(&s->base);
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/
// minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
double	sphere_intersect_distance(struct s_sphere *s, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	intersects[2];

	a = dot_product(ray.dir, ray.dir);
	b = 2 * dot_product(ray.dir, vec_sub(ray.loc, s->base.loc));
	c = pow(vec_length(vec_sub(ray.loc, s->base.loc)), 2)
		- pow(s->diameter / 2, 2);
	if (quadratic_solver(a, b, c, intersects))
	{
		if (fgreaterthan(intersects[0], 0))
			return (intersects[0]);
		if (fgreaterthan(intersects[1], 0))
			return (intersects[1]);
	}
	return (INFINITY);
}

t_color	sphere_intersect_color(struct s_sphere *s, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_vec		surface_normal;
	t_ray		impact_normal;

	(void)bounces;
	dist = sphere_intersect_distance(s, ray);
	if (dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, dist));
	surface_normal = vec_normalize(vec_sub(impact, s->base.loc));
	if (fgreaterthan(dot_product(ray.dir, surface_normal), 0))
		surface_normal = vec_neg(surface_normal);
	impact = vec_add(impact, vec_scal_mul(surface_normal, RT_EPSILON));
	impact_normal = (t_ray){impact, surface_normal};
	return (apply_shading(scene, s->base.col, impact_normal, ray));
}
