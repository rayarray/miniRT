/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:16:05 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 15:24:10 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shape_sphere.h"
#include "rt_typedef.h"
#include "math.h"
#include "rt_math.h"
#include "color.h"
#include "shading.h"

int	sphere_ctor(struct s_sphere *this, t_vec loc, double diameter, t_color color)
{
	static const struct s_shape_vtable	sphere_vtable = {
			(void (*)(struct s_shape *this))sphere_dtor,
			(double (*)(struct s_shape *this, t_ray ray))sphere_intersect_distance,
			(t_color (*)(struct s_shape *this, struct s_scene *scene, t_ray ray))sphere_intersect_color
		};

	shape_ctor(&this->base, e_SPHERE, loc, color);
	this->base.vtptr = &sphere_vtable;
	this->diameter = diameter;
	return (0);
}

void	sphere_dtor(struct s_sphere *this)
{
	_shape_base_dtor(&this->base);
}

t_color	sphere_hit_ray(struct s_sphere *this, struct s_scene *scene, t_ray ray)
{
	t_color	color;

	(void)scene;
	(void)ray;
	(void)this;
	color = this->base.col;
	return (color);
}

static double	geometric_intersect_distance(struct s_sphere *s, t_ray ray)
{
	t_vec	l;	// vector between origin and sphere
	double	tca;	// distance from origin to a line s that is perpendicular between destination line and l
	double	d;	// distance between s.loc and the line s above
	double	thc;	// distance between line s and impact point
	double result;

	// TODO consider double value inaccuracies
	l = vec_sub(s->base.loc, ray.point);
	tca = dot_product(l, ray.dir);
	if (flessthan(tca, 0))
		return (INFINITY);
	d = sqrt(dot_product(l, l) - pow(tca, 2));		// This sqrt could be optimized away if we let d be squared
	if (flessthan(d, 0) || fgreaterthan(d, s->diameter / 2))	// d should always be greater than or equal to zero but I guess it's better to be safe than sorry. second comparison checks if the intersection is outside the radius
		return (INFINITY);
	thc = sqrt(pow(s->diameter / 2, 2) - pow(d, 2));
	if (flessthan(tca - thc, 0) && flessthan(tca + thc, 0))
		return (INFINITY);
	if (fgreaterthan(tca - thc, 0) && fgreaterthan(tca + thc, 0))
		result = fmin(tca - thc, tca + thc);
	else
		result = fmax(tca - thc, tca + thc);
	return (result);
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
static double	analytic_intersect_distance(struct s_sphere *s, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	result;
	double	result1;
	double	result2;

	result = INFINITY;
	a = dot_product(ray.dir, ray.dir);		// should be always 1
	b = 2 * dot_product(ray.dir, vec_sub(ray.point, s->base.loc));
	c = pow(vec_length(vec_sub(ray.point, s->base.loc)), 2) - pow(s->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (a == 0)					// Would result in a divide by zero
		result = INFINITY;		// but this shouldn't happen because ray.dir should be normalized.
	if (feq(discriminant, 0))
		result = -b / (2 * a);
	else if (fgreaterthan(discriminant, 0))
	{ 
		result1 = (-b + sqrt(discriminant)) / (2 * a);	// Source material says this method might produce errors ("catastrophic cancellation")
		result2 = (-b - sqrt(discriminant)) / (2 * a);	// TODO replace with a better method
		if (flessthan(result1, 0) && flessthan(result2, 0))
			result = INFINITY;
		else if (fgreaterthan(result1, 0) && fgreaterthan(result2, 0))
			result = fmin(result1, result2);
		else
			result = fmax(result1, result2);
	}
	return (result);
}

// Returns INFINITY if ray does not intersect with s
double	sphere_intersect_distance(struct s_sphere *s, t_ray ray)
{
	double	anal;
	double	geom;

	anal = analytic_intersect_distance(s, ray);		// calculating distance using two methods for error checking. 
	geom = geometric_intersect_distance(s, ray);
	if (anal != INFINITY && geom != INFINITY && !feq(anal, geom))
		printf("sphere's geometric and analytic intersect differs by %f: anal %f geom %f!\n", anal - geom, anal, geom);
	return (anal);
}

t_color	sphere_intersect_color(struct s_sphere *s, struct s_scene *scene, t_ray ray)
{
	t_color	color;
	double	dist;
	t_point3	impact;
	t_vec	surface_normal;

	dist = sphere_intersect_distance(s, ray);
	color = s->base.col;
	if (dist != INFINITY)
	{
		impact = vec_add(ray.point, vec_scal_mul(ray.dir, dist));
		surface_normal = vec_normalize(vec_sub(impact, s->base.loc));
		color = apply_ambient(color, scene->ambient);
//		color = facing_ratio(surface_normal, ray.dir, color, color_fade(scene->ambient->color, scene->ambient->light_ratio));
		color = diffuse_shading(scene, surface_normal, impact, color);
	}
	return (color);
}
