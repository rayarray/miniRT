/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/10 12:02:40 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"
#include "math.h"
#include "rt_math.h"
#include "color.h"
#include "shading.h"

// debug includes
#include <stdio.h>

int	cylinder_ctor(struct s_cylinder *this, t_vec orientation[2],
	double dimensions[2], t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))cylinder_dtor,
		(double (*)(struct s_shape *, t_ray))cylinder_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		cylinder_intersect_color,
		(int (*)(struct s_shape *, t_point3))cylinder_within_shape
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
	this->bot = plane_eq(vecOrigo(), vec_neg(this->axis));
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
	//static int counter;

	ray.dir = unitVector(ray.dir);
	rc = vecSub(ray.loc, this->base.loc);
	nv = vecCross(ray.dir, this->axis);
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
	//if (++counter <= 10)
	//{
	//	vecPrint("nv", nv, 0);
	//	printf(" d:%f\n", d);
	//}
	if (fleq(d, this->radius))
	{
		ov = vecCross(rc, this->axis);
		t = -vecDot(ov, nv) / ln;
		ov = unitVector(vecCross(nv, this->axis));
		s = fabs(sqrt(this->rad2 - d * d) / vecDot(ray.dir, ov));
		hit->in = t - s;
		hit->out = t + s;
		//if (hit->in < 0 && hit->out < 0)
		//	printf("inf_cyl_intsec: both results negative! %f %f", hit->in, hit->out);
		// if (hit->in < 0)
		// 	hit->in = -INFINITY;
		// if (hit->out < 0)
		// 	hit->out = INFINITY;
		//ft_printf("int_cyl_intsec: in:%f out:%f", hit->in, hit->out);
		return (1);
	}
	return (0);
}

int	cylinder_end_cap(t_ray ray, t_surface_hits *hit, t_plane_eq plane)
{
	double	dc;
	double	dw;
	double	t;

	dc = plane.a * ray.dir.x + plane.b * ray.dir.y
		+ plane.c * ray.dir.z;
	dw = plane.a * ray.loc.x + plane.b * ray.loc.y
		+ plane.c * ray.loc.z + plane.d;
	if (feq(dc, 0.0)) // parallel to plane
	{
		if (fgeq(dw, 0.0))
			return (0);
	}
	else
	{
		t = -dw / dc;
		if (fgeq(dc, 0.0)) // if far plane
		{
			if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
			{
				hit->dist = t;
				hit->surf = hit->pass;
			}
			if (flessthan(t, hit->in))
				return (0);
		}
		return (0);
	}
	return (1);
}

double	cylinder_clip_cap(struct s_cylinder *this, t_ray ray, t_surface_hits *hit, t_plane_eq plane)
{
	double	dc;
	double	dw;
	double	t;

	dc = plane.a * ray.dir.x + plane.b * ray.dir.y
		+ plane.c * ray.dir.z;
	dw = plane.a * ray.loc.x + plane.b * ray.loc.y
		+ plane.c * ray.loc.z + plane.d;
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
				hit->surfout = hit->pass + 1;
			}
			if (flessthan(t, hit->in))
				return (INFINITY);
		}
		else // if near plane
		{
			if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
			{
				hit->in = t;
				hit->surfin = hit->pass + 1;
			}
			if (fgreaterthan(t, hit->out))
				return (INFINITY);
		}
	}
	if (++hit->pass == 1)
		return (cylinder_clip_cap(this, ray, hit, this->top));
	//if (hit->in < 0)
	//	hit->in = 0;
	//if (hit->out < 0)
	//	hit->out = INFINITY;
	if ((hit->surfin == CYL_BOT && hit->surfout == CYL_TOP) || (hit->surfin == CYL_TOP && hit->surfout == CYL_BOT))
		return (fmin(hit->in, hit->out));
	else if (hit->in < hit->out)
		return (hit->in);
	else
		return (INFINITY);
	// else if ((hit->surfin == CYL_BOT && hit->surfout == CYL_TOP) || (hit->surfin == CYL_TOP && hit->surfout == CYL_BOT))
	// {
	// 	hit->dist = fmin(hit->in, hit->out);
	// 	if (hit->dist >= 0)
	// 		return (hit->dist);
	// 	else
	// 		return (fmax(hit->in, hit->out));
	// }
	// else if (fgeq(hit->in, 0) && hit->in < hit->out)
	// 	return (hit->in);
	// else if (flessthan(hit->in, 0) && fgeq(hit->out, 0))
	// 	return (hit->out);
	//else
	//	return (INFINITY);
}

t_surface_hits	cylinder_intersect_hits(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits	hits;
	t_vec			origo;

	ft_bzero(&hits, sizeof(t_surface_hits));
	if (!infinite_cylinder_intersect(this, ray, &hits) && --hits.pass)
	{
		//printf("after infinite_cyl_intersect=0: in:%f out:%f\n", hits.in, hits.out);
		return (hits);
	}
	//printf("after infinite_cyl_intersect=1: in:%f out:%f\n", hits.in, hits.out);
	origo = this->base.loc;
	this->base.loc = vecOrigo();
	ray.loc = vecSub(ray.loc, origo);
	hits.dist = cylinder_clip_cap(this, ray, &hits, this->bot);
	//printf("after cyl_clip_cap: in:%f out:%f\n", hits.in, hits.out);
	this->base.loc = origo;
	if (hits.dist == hits.in)
		hits.surf = hits.surfin;
	else
		hits.surf = hits.surfout;
	return (hits);
}

t_vec cylinder_test(struct s_cylinder *this, t_ray ray)
{
	t_vec	flat;
	double	angle;

	flat = vecCross(ray.dir, this->axis);
	angle = this->axis.x * ray.dir.x + this->axis.y * ray.dir.y + this->axis.z * ray.dir.z;
	angle /= sqrt(pow(this->axis.x, 2.0f) + pow(this->axis.y, 2.0f) + pow(this->axis.z, 2.0f))
		* sqrt(pow(ray.dir.x, 2.0f) + pow(ray.dir.y, 2.0f) + pow(ray.dir.z, 2.0f));
	angle = acos(angle) * 180 / M_PI;
	printf("angle between camray & axis: %f\n", angle);
	
	return (unitVector(flat));
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
	}
	if (this->base.debug == 7357 && hits.dist != INFINITY && hits.pass != -1)
	{
		printf("cyl_inter_dist rval:%f\n dia:%f hght:%f\n", hits.dist, this->diameter, this->height);
		vecPrint("loc", this->base.loc, 1);
		vecPrint("axis", this->axis, 1);
		//printf("cyl_test: %f\n", cylinder_test(this, ray));
		//vecPrint("")
		vecPrint("cross camdir, axis:", cylinder_test(this, ray), 1);
	}
	if (hits.pass == -1)
	{
		//printf("cylinder_intersect_distance result:%f\n", hits.dist);
		return (INFINITY);
	}
	else
		return (hits.dist);
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

// https://www.flipcode.com/archives/Fast_Point-In-Cylinder_Test.shtml
int	cylinder_within_shape(struct s_cylinder *this, t_point3 loc)
{
	t_vec	d;
	t_vec	pd;
	double	dot;
	double	dsq;

	d = vecMul(this->axis, this->height);
	pd = vecSub(loc, this->base.loc);
	dot = pd.x * d.x + pd.y * d.y + pd.z * d.z;
	if (fleq(dot, 0.0) || fgreaterthan(dot, this->height * this->height))
		return (0);
	else
	{
		dsq = vecDot(pd, pd) - ((dot * dot) / (this->height * this->height));
		if (fgreaterthan(dsq, this->rad2 * 4))
			return (0);
		else
			return (1);
	}
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
	if (bounces > 7000)
		printf("cyl_int_col: in[%d:%f] out[%d:%f]\n", hit.surfin, hit.in, hit.surfout, hit.out);
	if (hit.pass == -1 || hit.dist == INFINITY)
		return ((t_color){0, 0, 0, 0xFF});
//	if (hit.dist < 0)
//		hit.dist = fmax(hit.in, hit.out);
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, hit.dist));
	surface_normal = cylinder_hit_normal(this, impact, hit.surf);
	if (this->base.cam_inside)
		surface_normal = vec_neg(surface_normal);
	if (bounces > 7000)
		vecPrint("surf_norm", surface_normal, 1);
	//if (!this->base.cam_inside)
	//	printf("cam_inside:%d\n", this->base.cam_inside);
	//impact = vec_add(impact, vec_scal_mul(surface_normal, 0.0000001));
	impact = vec_add(impact, vec_scal_mul(surface_normal, 0.00001));
	impact_normal = (t_ray){impact, surface_normal};
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
