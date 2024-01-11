/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:19:08 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cone_bonus.h"

static int	vec_eq(t_vec a, t_vec b)
{
	return (feq(a.x, b.x) && feq(a.y, b.y) && feq(a.z, b.z));
}

double	test_results(struct s_cone *c, t_ray ray,
	int results, double isects[2])
{
	t_cone_ray_pos	pos;

	pos = get_ray_position(c, ray);
	if (pos == e_OVER_CONE)
	{
		if (results == 1 && fgreaterthan(isects[0], 0) && vec_eq(vec_add(
					ray.loc, vec_scal_mul(ray.dir, isects[0])), c->vertex))
			return (check_hit_location(c, ray, isects[0]));
		else if (results == 2 && fgreaterthan(isects[1], 0))
			return (check_hit_location(c, ray, isects[1]));
		return (INFINITY);
	}
	else if (pos == e_BESIDE_CONE)
	{
		if (fgreaterthan(isects[0], 0))
			return (check_hit_location(c, ray, isects[0]));
		else if (results == 2 && fgreaterthan(isects[1], 0))
			return (check_hit_location(c, ray, isects[1]));
		return (INFINITY);
	}
	if (pos == e_INSIDE_CONE && fgreaterthan(isects[0], 0))
		return (check_hit_location(c, ray, isects[0]));
	else if (pos == e_INSIDE_CONE && results == 2 && fgreaterthan(isects[1], 0))
		return (check_hit_location(c, ray, isects[1]));
	return (cone_base_intersection(c, ray));
}

t_cone_ray_pos	get_ray_position(struct s_cone *c, t_ray ray)
{
	double		angle_between_ray_and_vertex;

	if (vec_eq(ray.loc, c->vertex))
		return (e_INSIDE_CONE);
	angle_between_ray_and_vertex = acos(
			dot_product(vec_normalize(vec_sub(ray.loc, c->vertex)), c->axis));
	if (flessthan(angle_between_ray_and_vertex, c->angle))
		return (e_OVER_CONE);
	angle_between_ray_and_vertex = acos(
			dot_product(vec_normalize(vec_sub(ray.loc, c->vertex)),
				vec_neg(c->axis)));
	if (flessthan(angle_between_ray_and_vertex, c->angle))
	{
		if (flessthan(cos(c->angle) * vec_length(
					vec_sub(c->vertex, ray.loc)), c->height))
			return (e_INSIDE_CONE);
		return (e_UNDER_CONE);
	}
	else
		return (e_BESIDE_CONE);
}

double	cone_base_intersection(struct s_cone *c, t_ray ray)
{
	double	distance;
	double	denom_base;
	t_vec	impact;

	denom_base = dot_product(c->axis, ray.dir);
	if (feq(denom_base, 0))
		return (INFINITY);
	distance = dot_product(vec_sub(c->base.loc, ray.loc), c->axis)
		/ denom_base;
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, distance));
	if (flessthan(distance, 0) || fgreaterthan(
			vec_distance(impact, c->base.loc), c->diameter / 2))
		return (INFINITY);
	return (distance);
}

double	check_hit_location(struct s_cone *c, t_ray ray, double distance)
{
	double	hit_height;

	hit_height = dot_product(vec_sub(c->vertex, vec_add(ray.loc,
					vec_scal_mul(ray.dir, distance))), c->axis);
	if (fgeq(hit_height, 0) && fleq(hit_height, c->height))
		;
	else if (fgreaterthan(hit_height, c->height))
		return (cone_base_intersection(c, ray));
	else if (flessthan(hit_height, 0))
		return (INFINITY);
	return (distance);
}
