/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/03 12:56:12 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"
#include "math.h"
#include "rt_math.h"
#include "color.h"
#include "shading.h"

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
	this->radius = this->diameter / 2;
	this->rad2 = this->radius * this->radius;
	this->height = dimensions[e_HEIGHT];
	this->axis = orientation[e_AXIS];
	this->axis = unitVector(orientation[e_AXIS]);
	this->center = vecAdd(this->base.loc, vecMul(this->axis, this->height / 2));
	this->bot = plane_eq(vecInit(0, 0, 0), vec_neg(this->axis));
	this->top = plane_eq(vecAdd(vecOrigo(), vecMul(this->axis, this->height)), this->axis);
	return (0);
}

void	cylinder_dtor(struct s_cylinder *this)
{
	_shape_base_dtor(&this->base);
}

int	infinite_cylinder_intersect(struct s_cylinder *this, t_ray ray, t_surface_hits *hit)
{
	t_vec	rc;
	t_vec	nv;
	double	ln;
	double	d;
	double	t;
	double	s;
	t_vec	dv;
	t_vec	ov;

	ray.destination = unitVector(ray.destination);
	rc = vecSub(ray.origin, this->base.loc);
	nv = vecCross(ray.destination, this->axis);
	ln = vecLength(nv);
	if (feq(ln, 0.0))
	{
		d = vecDot(rc, this->axis);
		dv = vecSub(rc, vecMul(this->axis, d));
		d = vecLength(dv);
		hit->in = -INFINITY;
		hit->out = INFINITY;
		return (fleq(d, this->radius));
	}
	nv = unitVector(nv);
	d = fabs(vecDot(rc, nv));
	if (fleq(d, this->radius))
	{
		ov = vecCross(rc, this->axis);
		t = -vecDot(ov, nv) / ln;
		ov = unitVector(vecCross(nv, this->axis));
		s = fabs(sqrt(this->rad2 - d * d) / vecDot(ray.destination, ov));
		hit->in = t - s;
		hit->out = t + s;
		return (1);
	}
	return (0);
}

double	cylinder_clip_cap(struct s_cylinder *this, t_ray ray, t_surface_hits *hit, t_plane_eq plane)
{
	double	dc;
	double	dw;
	double	t;

	hit->pass++; // first pass is CYL_BOT and second pass is CYL_TOP
	dc = plane.a * ray.destination.x + plane.b * ray.destination.y
		+ plane.c * ray.destination.z;
	dw = plane.a * ray.origin.x + plane.b * ray.origin.y
		+ plane.c * ray.origin.z + plane.d;
	if (feq(dc, 0.0)) // parallel to bottom
	{
		if (fgeq(dw, 0.0))
			return (INFINITY);
	}
	else
	{
		t = -dw / dc;
		if (fgeq(dc, 0.0)) // if far plane
		{
			if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
			{
				hit->out = t;
				hit->surfout = hit->pass;
			}
			if (flessthan(t, hit->in))
				return (INFINITY);
		}
		else // if near plane
		{
			if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
			{
				hit->in = t;
				hit->surfin = hit->pass;
			}
			if (fgreaterthan(t, hit->out))
				return (INFINITY);
		}
	}
	if (hit->pass == 1)
		return (cylinder_clip_cap(this, ray, hit, this->top));
	else if ((hit->surfin == CYL_BOT && hit->surfout == CYL_TOP) || (hit->surfin == CYL_TOP && hit->surfout == CYL_BOT))
		return (fmin(hit->in, hit->out));
	else if (hit->in < hit->out)
		return (hit->in);
	else
		return (INFINITY);
}

t_surface_hits	cylinder_intersect_hits(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits	hits;
	t_vec			origo;

	ft_bzero(&hits, sizeof(t_surface_hits));
	if (!infinite_cylinder_intersect(this, ray, &hits) && --hits.pass)
		return (hits);
	origo = this->base.loc;
	this->base.loc = vecOrigo();
	ray.origin = vecSub(ray.origin, origo);
	hits.in = cylinder_clip_cap(this, ray, &hits, this->bot);
	this->base.loc = origo;
	if (hits.in == INFINITY)
		return (hits);
	if (hits.in > hits.out)
	{
		hits.in = hits.out;
		hits.surfin = hits.surfout;
	}
	return (hits);
}

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits	hits;

	hits = cylinder_intersect_hits(this, ray);
	if (hits.pass == -1)
		return (INFINITY);
	else
		return (hits.in);
}

t_vec	cylinder_hit_normal(struct s_cylinder *this, t_point3 impact, int hit_side)
{
	double	t;
	t_vec	pt;

	if (hit_side == CYL_BOT)
		return (vec_neg(this->axis));
	else if (hit_side == CYL_TOP)
		return (this->axis);
	t = vecDot(vecSub(impact, this->base.loc), this->axis);
	pt = vecAdd(this->base.loc, vecMul(this->axis, t));
	return (unitVector(vecSub(impact, pt)));
}

t_color	cylinder_intersect_color(struct s_cylinder *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	t_point3	impact;
	t_vec		surface_normal;
	t_ray		impact_normal;
	t_surface_hits	hit;

	(void)bounces;
	hit = cylinder_intersect_hits(this, ray);
	if (hit.pass == -1 || hit.in == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.origin, vec_scal_mul(ray.destination, hit.in));
	surface_normal = cylinder_hit_normal(this, impact, hit.surfin);
	impact = vec_add(impact, vec_scal_mul(surface_normal, 0.00001));
	impact_normal = (t_ray){impact, surface_normal};
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
