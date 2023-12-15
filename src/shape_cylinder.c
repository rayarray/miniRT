/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/15 15:18:47 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "shading.h"
#include "color.h"


#include <stdio.h>
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
	this->dia2 = this->diameter * this->diameter;
	this->height = dimensions[e_HEIGHT];
	this->axis = unitVector(orientation[e_AXIS]);
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

double	interSectPlane(struct s_cylinder *this, t_ray ray)
{
	double	denom;
	double	t;
	t_vec	cyl_loc_cam_loc;

	t = -1;
	denom = vecDot(this->axis, ray.destination);
	if (denom > RT_EPSILON)
	{
		cyl_loc_cam_loc = vecSub(this->base.loc, ray.origin);
		t = vecDot(cyl_loc_cam_loc, this->axis) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1);
}

double	interSectPlane2(struct s_cylinder *this, t_ray ray)
{
	double	distance;
	double	denom;

	distance = -1;
	denom = vecDot(this->axis, ray.destination);
	if (!feq(denom, 0))
		distance = vecDot(vecSub(this->base.loc, ray.origin), this->axis)
			/ denom;
	if (flessthan(distance, 0))
		distance = INFINITY;
	//if (fleq(ray.destination.y, 0) && distance != INFINITY)
	//	printf("cyl dist = %f\n", distance);
	return (distance);
}

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	double	distance;
	double	t;
	double	d2;
	t_vec	p;
	t_vec	v;
	static int	onlyonce;

	if (!onlyonce)
	{
		vecPrint("cyl axis", this->axis, ++onlyonce);
		ray.destination = unitVector(ray.destination);
		vecPrint("cam dir ", ray.destination, 1);
	}
	ray.destination = unitVector(ray.destination);
	distance = INFINITY;
	//ray.origin = vecSub(ray.origin, this->base.loc);
	t = interSectPlane2(this, ray);
	if (t >= 0 && t < INFINITY)
	{
		p = vecAdd(ray.origin, vecMul(ray.destination, t));
		v = vecSub(p, this->base.loc);
		d2 = vecDot(v, v);
		if (d2 <= this->dia2)
		{
			//printf("d2 = %f\n", d2);
			return (t);
		}
	}
	return (distance);	// placeholder
}

t_color	cylinder_intersect_color(struct s_cylinder *this,
	struct s_scene *scene, t_ray ray, int bounces)
{
	t_color		color;
	double		dist;
	t_point3	impact;
	t_vec		normal_to_ray;

	dist = cylinder_intersect_distance(this, ray);
	impact = vecAdd(ray.origin, vecMul(ray.destination, dist));
	normal_to_ray = this->axis;
	color = apply_ambient(scene->ambient);
	color = diffuse_shading(scene, (t_ray){impact, normal_to_ray}, color);
	color = color_mix(this->base.col, color);
	color = specular_lighting(scene, (t_ray){impact, normal_to_ray}, ray, color);
	(void)bounces;
	return (color);	//placeholder
}
