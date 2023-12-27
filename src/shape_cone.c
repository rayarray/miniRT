/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/20 00:01:41 by tsankola         ###   ########.fr       */
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
	if (!is_direction_vector(orientation[e_CONE_AXIS]))
		return (1);
	this->diameter = dimensions[e_CONE_DIAMETER];
	this->height = dimensions[e_CONE_HEIGHT];
	this->axis = vec_normalize(orientation[e_CONE_AXIS]);
	return (0);
}

void	cone_dtor(struct s_cone *this)
{
	_shape_base_dtor(&this->base);
}

double	cone_intersect_distance(struct s_cone *this, t_ray ray)
{
	double results[3];

	results[0] = INFINITY;

	double cq = pow(this->diameter / 2, 2) / pow(this->height, 2);
	double a = dot_product(ray.destination, ray.destination) - (cq - 1) * pow(dot_product(ray.destination, vec_neg(this->axis)), 2);
	t_vec ct = vec_add(this->base.loc, vec_scal_mul(vec_neg(this->axis), this->height));
	t_vec rl = vec_sub(ray.origin, ct);
	double b = 2 * ((dot_product(rl, ray.destination) - (cq + 1) * dot_product(rl, vec_neg(this->axis)) * dot_product(ray.destination, vec_neg(this->axis))));
	double c = dot_product(rl, rl) - (cq + 1) * pow(dot_product(rl, vec_neg(this->axis)), 2);
	double discriminant = pow(b, 2) - 4 * a * c;
	if (feq(discriminant, 0))
			results[0] = -b / (2 * a);
	else if (fgreaterthan(discriminant, 0))
	{
		results[1] = (-b + sqrt(discriminant)) / (2 * a);	// Source material says this method might produce errors ("catastrophic cancellation")
		results[2] = (-b - sqrt(discriminant)) / (2 * a);	// TODO replace with a better method
		if (fgreaterthan(results[1], 0) && fgreaterthan(results[2], 0))
			results[0] = fmin(results[1], results[2]);
		else if (!(flessthan(results[1], 0) && flessthan(results[2], 0)))
			results[0] = fmax(results[1], results[2]);
	}

/* 	denom_base = dot_product(this->axis, ray.destination);
	if (!feq(denom_base, 0))
		distance = dot_product(vec_sub(this->base.loc, ray.origin), this->axis)
			/ denom_base;
	impact = vec_add(ray.origin, vec_scal_mul(ray.destination, distance));
	if (flessthan(distance, 0) || fgreaterthan(vec_distance(impact, this->base.loc), this->diameter / 2))
		distance = INFINITY;
 */	return (results[0]);
}

t_color	cone_intersect_color(struct s_cone *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_ray		impact_normal;

	(void)bounces;
	dist = cone_intersect_distance(this, ray);
	if (dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.origin, vec_scal_mul(ray.destination, dist));
	if (dot_product(this->axis, ray.destination) && fleq(vec_distance(impact, this->base.loc), this->diameter / 2)) {
		impact_normal = (t_ray){impact, this->axis};
		if (fgreaterthan(dot_product(ray.destination, this->axis), 0))
			impact_normal.destination = vec_neg(impact_normal.destination);
	}
	else
	{
//		t_vec v_p = vec_normalize(vec_sub(this->base.loc, impact));
		t_vec tip = vec_scal_mul(this->axis, this->height);
//		tip * x = impact => x = impact / tip;
		t_vec tip_impact = vec_sub(vec_add(this->base.loc, tip), impact);
		double theta = acos(dot_product(tip_impact, vec_neg(tip)) / vec_length(tip_impact) / vec_length(tip));
		t_vec normal = vec_neg(vec_scal_mul(tip_impact, tan(theta)));
		impact_normal = (t_ray){impact, normal};
	}
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}