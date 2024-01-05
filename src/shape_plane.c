/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:39:10 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/04 11:41:33 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_plane.h"
#include "rt_validations.h"
#include "shading.h"
#include "color.h"

int	plane_ctor(struct s_plane *plane, t_vec point, t_vec normal, t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))plane_dtor,
		(double (*)(struct s_shape *, t_ray))plane_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		plane_intersect_color,
		(int (*)(struct s_shape *, t_point3))plane_within_shape
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
	denom = dot_product(this->normal, ray.dir);
	if (!feq(denom, 0))
		distance = dot_product(vec_sub(this->point, ray.loc), this->normal)
			/ denom;
	if (flessthan(distance, 0))
		distance = INFINITY;
	return (distance);
}

t_color	plane_intersect_color(struct s_plane *p, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_ray		impact_normal;

	(void)bounces;
	dist = plane_intersect_distance(p, ray);
	if (dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, dist));
	impact_normal = (t_ray){impact, p->normal};
	if (fgreaterthan(dot_product(ray.dir, p->normal), 0))
		impact_normal.dir = vec_neg(impact_normal.dir);
	impact_normal.loc = vec_add(impact_normal.loc, 
		vec_scal_mul(impact_normal.dir, 0.00001));
	return (apply_shading(scene, p->base.col, impact_normal, ray));
}

int	plane_within_shape(struct s_plane *this, t_point3 loc)
{
	(void)this;
	(void)loc;
	return (0);
}
