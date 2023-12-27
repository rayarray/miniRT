/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/27 20:51:10 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cone.h"
#include "rt_validations.h"
#include "rt_typedef.h"
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
		|| fleq(dimensions[e_CONE_HEIGHT], 0)	// Perhaps this could be negative? TODO: Test if feasible
		|| fleq(dimensions[e_CONE_DIAMETER], 0))
		return (1);
	this->diameter = dimensions[e_CONE_DIAMETER];
	this->height = dimensions[e_CONE_HEIGHT];
	this->axis = vec_normalize(orientation[e_CONE_AXIS]);
	this->angle = atan2(this->diameter / 2, this->height);
	this->vertex = vec_add(this->base.loc, vec_scal_mul(this->axis, this->height));
	return (0);
}

void	cone_dtor(struct s_cone *this)
{
	_shape_base_dtor(&this->base);
}

// https://davidjcobb.github.io/articles/ray-cone-intersection
double	cone_intersect_distance(struct s_cone *this, t_ray ray)
{
 	double	cq;	// cone ratio squared: (radius / height) ^ 2
	double	a;
	double	b;
	double	c;
	double	distance;
	t_vec	rl;

	t_vec	ca;

	ca = this->axis;

	cq = pow(this->diameter / 2, 2) / pow(this->height, 2);
	a = dot_product(ray.destination, ray.destination) - (cq + 1) * pow(dot_product(ray.destination, ca), 2);
	rl = vec_sub(ray.origin, this->vertex);
	b = 2 * ((dot_product(rl, ray.destination) - (cq + 1) * dot_product(rl, ca) * dot_product(ray.destination, ca)));
	c = dot_product(rl, rl) - (cq + 1) * pow(dot_product(rl, ca), 2);
	distance = min_pos_discriminant(a, b, c);

	double hit_position = dot_product(vec_sub(this->vertex, vec_scal_mul(ray.destination, distance)), ca);
	if (!fgeq(hit_position, 0) || !fleq(hit_position, vec_length(vec_sub(this->vertex, this->base.loc))))
		distance = INFINITY;
	else
	{
		double denom_base = dot_product(ca, ray.destination);
		if (!feq(denom_base, 0))
			distance = dot_product(vec_sub(this->base.loc, ray.origin), this->axis)
				/ denom_base;
		t_vec impact = vec_add(ray.origin, vec_scal_mul(ray.destination, distance));
		if (flessthan(distance, 0) || fgreaterthan(vec_distance(impact, this->base.loc), this->diameter / 2))
			distance = INFINITY;
	}
	return (distance);
}

t_color	cone_intersect_color(struct s_cone *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_ray		impact_normal;
	t_vec		normal;

	(void)bounces;
	//return this->base.col;
	dist = cone_intersect_distance(this, ray);
	if (dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.origin, vec_scal_mul(ray.destination, dist));
	if (dot_product(this->axis, ray.destination) && fleq(vec_distance(impact, this->base.loc), this->diameter / 2))
		impact_normal = (t_ray){impact, this->axis};
	else
	{
		normal = vec_normalize(vec_sub(vec_scal_mul(this->axis, 1 / cos(this->angle)),
								 vec_normalize(vec_sub(this->vertex, impact))));
		impact_normal = (t_ray){impact, normal};
	}
	if (fgreaterthan(dot_product(ray.destination, impact_normal.destination), 0))
		impact_normal.destination = vec_neg(impact_normal.destination);
//	impact_normal.destination = vec_scal_mul(impact_normal.destination, 1.00001);
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
