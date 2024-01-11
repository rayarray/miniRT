/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder_bonus.h"
#include "rt_validations_bonus.h"
#include "rt_typedef_bonus.h"
#include "color_bonus.h"
#include "shading_bonus.h"

int	cylinder_ctor(struct s_cylinder *this, t_vec orientation[2],
	double dimensions[2], t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))cylinder_dtor,
		(double (*)(struct s_shape *, t_ray))cylinder_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		cylinder_intersect_color
	};

	shape_ctor(&this->base, e_CYLINDER, orientation[e_LOCATION], color);
	this->base.vtptr = &vtable;
	if (!is_direction_vector(orientation[e_AXIS]))
		return (1);
	this->diameter = dimensions[e_DIAMETER];
	this->radius = this->diameter / 2;
	this->rad2 = this->radius * this->radius;
	this->height = dimensions[e_HEIGHT];
	this->axis = orientation[e_AXIS];
	this->axis = vec_normalize(orientation[e_AXIS]);
	this->center = vec_add(this->base.loc,
			vec_scal_mul(this->axis, this->height / 2));
	this->bot = plane_eq((t_vec){0, 0, 0}, vec_neg(this->axis));
	this->top = plane_eq(vec_add((t_vec){0, 0, 0},
				vec_scal_mul(this->axis, this->height)), this->axis);
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits	hits;

	hits = cylinder_intersect_hits(this, ray);
	if (hits.dist < 0)
	{
		if (hits.dist == hits.in)
			hits.surf = hits.surfout;
		else
			hits.surf = hits.surfin;
		hits.dist = fmax(hits.in, hits.out);
		if (hits.dist < 0)
			return (INFINITY);
	}
	if (hits.pass == -1)
		return (INFINITY);
	else
		return (hits.dist);
}

t_vec	cylinder_hit_normal(struct s_cylinder *this,
		t_point3 impact, int hit_side)
{
	double	t;
	t_vec	pt;

	if (hit_side == CYL_BOT)
		return (vec_neg(this->axis));
	else if (hit_side == CYL_TOP)
		return (this->axis);
	t = dot_product(vec_sub(impact, this->base.loc), this->axis);
	pt = vec_add(this->base.loc, vec_scal_mul(this->axis, t));
	return (vec_normalize(vec_sub(impact, pt)));
}

t_color	cylinder_intersect_color(struct s_cylinder *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	t_point3		impact;
	t_vec			surface_normal;
	t_ray			impact_normal;
	t_surface_hits	hit;

	(void)bounces;
	hit = cylinder_intersect_hits(this, ray);
	if (hit.pass == -1 || hit.dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, hit.dist));
	surface_normal = cylinder_hit_normal(this, impact, hit.surf);
	if (cylinder_within_shape(this, ray.loc))
		surface_normal = vec_neg(surface_normal);
	impact = vec_add(impact, vec_scal_mul(surface_normal, 0.0001));
	impact_normal = (t_ray){impact, surface_normal};
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
