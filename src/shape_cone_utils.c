/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:19:08 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/05 02:02:21 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cone.h"

t_cone_ray_pos	get_ray_position(struct s_cone *cone, t_ray ray)
{
	double		angle_between_ray_and_vertex;
	
	angle_between_ray_and_vertex = acos(
		dot_product(vec_normalize(vec_sub(ray.loc, cone->vertex)), cone->axis));
	if (flessthan(angle_between_ray_and_vertex, cone->angle))
		return (e_OVER_CONE);
	angle_between_ray_and_vertex = acos(
		dot_product(vec_normalize(vec_sub(ray.loc, cone->vertex)), 
			vec_neg(cone->axis)));
	if (flessthan(angle_between_ray_and_vertex, cone->angle))
	{
		if (flessthan(cos(cone->angle) * vec_length(
				vec_sub(cone->vertex, ray.loc)), cone->height))
			return (e_INSIDE_CONE);
		return (e_UNDER_CONE);
	}
	else
		return (e_BESIDE_CONE);
}

double	cone_base_intersection(struct s_cone *cone, t_ray ray)
{
	double	distance;
	double	denom_base;
	t_vec	impact;

	denom_base = dot_product(cone->axis, ray.dir);
	if (feq(denom_base, 0))
		return (INFINITY);
	distance = dot_product(vec_sub(cone->base.loc, ray.loc), cone->axis)
		/ denom_base;
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, distance));
	if (flessthan(distance, 0) || fgreaterthan(
			vec_distance(impact, cone->base.loc), cone->diameter / 2))
		return (INFINITY);
	return (distance);
}

double	check_hit_location(struct s_cone *this, t_ray ray, double distance)
{
	double	hit_height;

	hit_height = dot_product(vec_sub(this->vertex, vec_add(ray.loc,
			vec_scal_mul(ray.dir, distance))), this->axis);
 	if (fgeq(hit_height, 0) && fleq(hit_height, this->height))
		;
	else if (fgreaterthan(hit_height, this->height))
		return (cone_base_intersection(this, ray));
	else if (flessthan(hit_height, 0))
		return (INFINITY);
	return (distance);
}
