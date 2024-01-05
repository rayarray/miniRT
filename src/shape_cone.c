/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:09 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/05 02:07:25 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shape_cone.h"
#include "rt_validations.h"
#include "shading.h"

int	cone_ctor(struct s_cone *this, t_vec orientation[2],
	double dimensions[2], t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))cone_dtor,
		(double (*)(struct s_shape *, t_ray))cone_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		cone_intersect_color
	};

	shape_ctor(&this->base, e_CONE, orientation[e_CONE_LOCATION], color);
	this->base.vtptr = &vtable;
	if (!is_direction_vector(orientation[e_CONE_AXIS])
		|| fleq(dimensions[e_CONE_HEIGHT], 0)
		|| fleq(dimensions[e_CONE_DIAMETER], 0))
		return (1);
	this->diameter = dimensions[e_CONE_DIAMETER];
	this->height = dimensions[e_CONE_HEIGHT];
	this->axis = vec_normalize(orientation[e_CONE_AXIS]);
	this->angle = atan2(this->diameter / 2, this->height);
	this->vertex = vec_add(this->base.loc,
		vec_scal_mul(this->axis, this->height));
	return (0);
}

void	cone_dtor(struct s_cone *this)
{
	_shape_base_dtor(&this->base);
}

static double	test_results(struct s_cone *this, t_ray ray,
	int results, double isects[2])
{
	t_cone_ray_pos ray_pos;
	
	ray_pos = get_ray_position(this, ray);
	if (ray_pos == e_OVER_CONE)	// Over cone. Only the side or tip can be visible.
	{
		if (results == 1 && fgreaterthan(isects[0], 0) && vec_eq(vec_add(
				ray.loc, vec_scal_mul(ray.dir, isects[0])), this->vertex))
			return (check_hit_location(this, ray, isects[0]));
		else if (results == 2 && fgreaterthan(isects[1], 0))
			return (check_hit_location(this, ray, isects[1]));
		return (INFINITY);
	}
	else if (ray_pos == e_BESIDE_CONE)	// Beside cone. The side can be visible and the bottom can be visible.
	{
		if (fgreaterthan(isects[0], 0))
			return (check_hit_location(this, ray, isects[0]));
		else if (results == 2 && fgreaterthan(isects[1], 0))
			return (check_hit_location(this, ray, isects[1]));
		return (INFINITY);
	}
	if (ray_pos == e_INSIDE_CONE && fgreaterthan(isects[0], 0))
		return (check_hit_location(this, ray, isects[0]));
	else if (ray_pos == e_INSIDE_CONE && results == 2 && fgreaterthan(isects[1], 0))
		return (check_hit_location(this, ray, isects[1]));
	return (cone_base_intersection(this, ray));
}

// https://davidjcobb.github.io/articles/ray-cone-intersection
double	cone_intersect_distance(struct s_cone *this, t_ray ray)
{
 	double	cq;	// cone ratio squared: (radius / height) ^ 2
	t_vec	ca;
	t_vec	rl;			// vector from ray origin to vertex
	double	terms[3];
	double	isects[2];
	int		results;

	ca = vec_neg(this->axis);
	cq = pow(this->diameter / 2, 2) / pow(this->height, 2);
	rl = vec_sub(ray.loc, this->vertex);
	terms[0] = dot_product(ray.dir, ray.dir) - (cq + 1) * pow(dot_product(ray.dir, ca), 2);
	terms[1] = 2 * ((dot_product(rl, ray.dir) - (cq + 1) * dot_product(rl, ca) * dot_product(ray.dir, ca)));
	terms[2] = dot_product(rl, rl) - (cq + 1) * pow(dot_product(rl, ca), 2);
	results = quadratic_solver(terms[0], terms[1], terms[2], isects);
	if (results == 0)	// TODO fix? Should not return always because if inside cone, we might be looking downwards and need to test the base intersection
		return (INFINITY);	// Although even in that case there should be at least one (negative) result.

	return (test_results(this, ray, results, isects));
}

t_color	cone_intersect_color(struct s_cone *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_ray		impact_normal;
	t_vec		normal;
	t_vec		spine_vec;

	(void)bounces;
	dist = cone_intersect_distance(this, ray);
	if (isinf(dist))
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, dist));
	if (feq(cone_base_intersection(this, ray), dist))
		impact_normal = (t_ray){impact, vec_neg(this->axis)};
	else
	{
		spine_vec = vec_scal_mul(vec_neg(this->axis), 1 / cos(this->angle));
		normal = vec_normalize(vec_sub(
				vec_normalize(vec_sub(impact, this->vertex)), spine_vec));
		impact_normal = (t_ray){impact, normal};
	}
	if (get_ray_position(this, ray) == e_INSIDE_CONE)
		impact_normal.dir = vec_neg(impact_normal.dir);
	impact_normal.loc = vec_add(impact_normal.loc, 
		vec_scal_mul(impact_normal.dir, RT_EPSILON));
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
