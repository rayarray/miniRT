/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/21 13:44:56 by rleskine         ###   ########.fr       */
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
	this->radius = this->diameter / 2;
	this->rad2 = this->radius * this->radius;
	this->height = dimensions[e_HEIGHT];
	this->axis = unitVector(orientation[e_AXIS]);
	this->center = vecAdd(this->base.loc, vecMul(this->axis, this->height / 2));
	this->bot = plane_eq(this->base.loc, vecSub(vecInit(0, 0, 0), this->axis));
	this->top = plane_eq(vecAdd(this->base.loc,
				vecMul(this->axis, this->height)), this->axis);
	// vecSub(vecInit(0, 0, 0), this->axis)
	printf("bot a%f b%f c%f d%f\n", this->bot.a, this->bot.b, this->bot.c, this->bot.d);
	printf("top a%f b%f c%f d%f\n", this->top.a, this->top.b, this->top.c, this->top.d);
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

//this is code for 2d disk intersect
double	disk_intersect_distance(struct s_cylinder *this, t_ray ray)
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
			return (t);
	}
	return (distance);	// placeholder
}

int	cylinderCapIntersect(struct s_cylinder *this, t_ray ray)
{
	double	distance;
	t_vec	temp;

	distance = disk_intersect_distance(this, ray);
	if (flessthan(distance, INFINITY))
		return (1);
	temp = this->base.loc;
	this->base.loc = vecAdd(this->base.loc, vecMul(this->axis, this->height));
	distance = disk_intersect_distance(this, ray);
	this->base.loc = temp;
	if (flessthan(distance, INFINITY))
		return (1);
	return (0);
}

// int	cylinder_clip(struct s_cylinder *this, t_ray ray, double *in, double *out)
// {
// 	int		surfin;
// 	int		surfout;
// 	double	dc;
// 	double	dw;
// 	double	t;
// 	surfin = CYL_SIDE;
// 	surfout = CYL_SIDE;
// 	dc = this->bot.a * ray.destination.x + this->bot.b * ray.destination.y
// 		+ this->bot.c * ray.destination.z;
// 	dw = this->bot.a * ray.origin.x + this->bot.b * ray.origin.y
// 		+ this->bot.c * ray.origin.z + this->bot.d;
// 	if (fleq(dc, 0.0)) { // if parallel to bottom plane
// 		if (fgeq(dw, 0.0))
// 			return (INFINITY);
// 		else
// 		{
// 			t = -dw / dc;
// 			if (fgeq(dc, 0.0)) // if far plane
// 			{
// 				if (flgt(t, in) && flessthan(t, out))
// 				{
// 					out = t;
// 					surfout = CYL_BOT;
// 				}
// 				if (flessthan(t, in))
// 					return (INFINITY);
// 			}
// 			else
// 			{
// 				if (flgt(t, in) && flessthan(t, out))
// 				{
// 					in = t;
// 					surfin = CYL_BOT;
// 				}
// 				if (flgt(t, out))
// 					return (INFINITY);
// 			}
// 		}
// 	}
// }

double	cylinder_clip_cap(struct s_cylinder *this, t_ray ray, t_surface_hits *hit, t_plane_eq plane)
{
	double	dc;
	double	dw;
	double	t;
	static int onlyonce;

	hit->pass++; // first pass is CYL_BOT and second pass is CYL_TOP
	if (!onlyonce || onlyonce != hit->pass)
	{
		printf("plane a%f b%f c%f d%f\n", plane.a, plane.b, plane.c, plane.d);
		onlyonce++;
	}
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
	//printf("running [%d] pass of cylclipcap\n", hit->pass);
	if (hit->pass == 1)
		return (cylinder_clip_cap(this, ray, hit, this->top));
	else if (hit->in < hit->out)
		return (hit->in);
	else
		return (INFINITY);
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

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits	hits;
	static int onlyonce;
	double rval;

	ft_bzero(&hits, sizeof(t_surface_hits));
	//if (this->base.debug || this->debug)
	//	printf("debug intersect: calling infinite_cylinder_intersect\n");
	if (!infinite_cylinder_intersect(this, ray, &hits))
		return (INFINITY);
	if (this->base.debug || this->debug) {
		//printf("surfin:%d surfout:%d\nin:%f\nout:%f\n", hits.surfin, hits.surfout, hits.in, hits.out);
		onlyonce = 1;
	}
	rval = cylinder_clip_cap(this, ray, &hits, this->bot);
	if (this->debug) {
		//printf("dist:%f surfin:%d surfout:%d\nin:%f\nout:%f\n", rval, hits.surfin, hits.surfout, hits.in, hits.out);
		onlyonce = 2;
	}
	return rval;
}

// double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray)
// {
// 	t_vec	rc;
// 	double	d;
// 	double	t;
// 	double	s;
// 	double	len;
// 	t_vec	nv;
// 	//t_vec	dv;
// 	t_vec	ov;
// 	static int	onlyonce;

// 	ray.destination = unitVector(ray.destination);
// 	d = disk_intersect_distance(this, ray);
// 	if (flessthan(d, INFINITY))
// 		return (d);
// 	rc = this->base.loc;
// 	this->base.loc = vecAdd(this->base.loc, vecMul(this->axis, this->height));
// 	d = disk_intersect_distance(this, ray);
// 	this->base.loc = rc;
// 	if (flessthan(d, INFINITY))
// 		return (d);
//  	if (!onlyonce)
//  	{
// 		vecPrint("cyl axis", this->axis, ++onlyonce);
//  		//ray.destination = unitVector(ray.destination);
//  		vecPrint("cam dir ", ray.destination, 1);
// 		printf("cyl axis len %f, cam dir len %f\n", vecLength(this->axis), vecLength(ray.destination));
//  	}
// 	rc = vecSub(ray.origin, this->base.loc);
// 	nv = vecCross(ray.destination, this->axis);
// 	// if (vecLengthSquared(nv) <= RT_EPSILON) */ ray parallel to cylinder */
// 	// {
// 	// 	d = vecDot(rc, this->axis);
// 	// 	dv.x = rc.x - d * this->axis.x;
// 	// 	dv.y = rc.y - d * this->axis.y;
// 	// 	dv.z = rc.z - d * this->axis.z;
// 	// 	d = vecLength(dv);
// 	// 	if (d <= this->diameter)
// 	// 		return (1);
// 	// 	else
// 	// 		return (INFINITY);
// 	// }
// 	len = vecLength(nv);
// 	nv = unitVector(nv);
// 	d = fabs(vecDot(rc, nv));
// 	if (d <= this->diameter)
// 	{
// 		ov = vecCross(rc, this->axis);
// 		t = - vecDot(ov, nv) / len;
// 		ov = unitVector(vecCross(nv, this->axis));
// 		s = fabs(sqrt(this->dia2 - (d * d)) / vecDot(ray.destination, ov));
// 		ray.destination = vecAdd(ray.origin, vecMul(ray.destination, t + s));
// 		ray.origin = vecAdd(this->base.loc, vecMul(this->axis, this->height / 2));
// 		ray.destination = unitVector(vecSub(ray.destination, ray.origin));
// 		//if (cylinderCapIntersect(this, ray))
// 		//	return (INFINITY);
// 		//printf("t - s:[%f]\n", s - t);
// 		return (t + s);
// 	}
// 	return (INFINITY);
// }

t_color	cylinder_intersect_color(struct s_cylinder *this,
	struct s_scene *scene, t_ray ray, int bounces)
{
	t_color		color;
	double		dist;
	t_point3	impact;
	t_vec		normal_to_ray;

	// if (bounces == -2) {
	// 	this->debug = 1;
	// 	printf("debug at intersect_color\n");
	// 	dist = cylinder_intersect_distance(this, ray);
	// 	this->debug = 0;
	// }
	// else
	dist = cylinder_intersect_distance(this, ray);
	impact = vecAdd(ray.origin, vecMul(ray.destination, dist));
	normal_to_ray = unitVector(vecSub(impact, this->center));
	color = apply_ambient(scene->ambient);
	color = diffuse_shading(scene, (t_ray){impact, normal_to_ray}, color);
	color = color_mix(this->base.col, color);
	color = specular_lighting(scene, (t_ray){impact, normal_to_ray}, ray, color);
	(void)bounces;
	return (color);	//placeholder
}
