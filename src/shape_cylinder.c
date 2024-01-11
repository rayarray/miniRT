/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 10:55:25 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"
#include "color.h"
#include "shading.h"

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

int	infinite_cylinder_intersect(struct s_cylinder *this, t_ray ray, t_surface_hits *hit)
{
	t_cylinder_products	var;

	ray.dir = vec_normalize(ray.dir);
	var.rc = vec_sub(ray.loc, this->base.loc);
	var.nv = cross_product(ray.dir, this->axis);
	var.ln = vec_length(var.nv);
	if (feq(var.ln, 0.0))
	{
		var.d = dot_product(var.rc, this->axis);
		var.dv = vec_sub(var.rc, vec_scal_mul(this->axis, var.d));
		var.d = vec_length(var.dv);
		hit->in = -INFINITY;
		hit->out = INFINITY;
		return (fleq(var.d, this->radius));
	}
	var.nv = vec_normalize(var.nv);
	var.d = fabs(dot_product(var.rc, var.nv));
	if (fleq(var.d, this->radius))
	{
		var.ov = cross_product(var.rc, this->axis);
		var.t = -dot_product(var.ov, var.nv) / var.ln;
		var.ov = vec_normalize(cross_product(var.nv, this->axis));
		var.s = fabs(sqrt(this->rad2 - var.d * var.d)
				/ dot_product(ray.dir, var.ov));
		hit->in = var.t - var.s;
		hit->out = var.t + var.s;
		return (1);
	}
	return (0);
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
	if (feq(dc, 0.0))
	{
		if (fgeq(dw, 0.0))
			return (INFINITY);
	}
	else
	{
		t = -dw / dc;
		if (fgeq(dc, 0.0))
		{
			if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
			{
				hit->out = t;
				hit->surfout = hit->pass + 1;
			}
			if (flessthan(t, hit->in))
				return (INFINITY);
		}
		else
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
	if ((hit->surfin == CYL_BOT && hit->surfout == CYL_TOP) || (hit->surfin == CYL_TOP && hit->surfout == CYL_BOT))
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
	this->base.loc = (t_vec){0, 0, 0};
	ray.loc = vec_sub(ray.loc, origo);
	hits.dist = cylinder_clip_cap(this, ray, &hits, this->bot);
	this->base.loc = origo;
	if (hits.dist == hits.in)
		hits.surf = hits.surfin;
	else
		hits.surf = hits.surfout;
	return (hits);
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

// https://www.flipcode.com/archives/Fast_Point-In-Cylinder_Test.shtml
int	cylinder_within_shape(struct s_cylinder *this, t_point3 loc)
{
	t_vec	d;
	t_vec	pd;
	double	dot;
	double	dsq;

	d = vec_scal_mul(this->axis, this->height);
	pd = vec_sub(loc, this->base.loc);
	dot = pd.x * d.x + pd.y * d.y + pd.z * d.z;
	if (fleq(dot, 0.0) || fgreaterthan(dot, this->height * this->height))
		return (0);
	else
	{
		dsq = dot_product(pd, pd) - ((dot * dot) / (this->height * this->height));
		if (fgreaterthan(dsq, this->rad2 * 4))
			return (0);
		else
			return (1);
	}
}

t_vec	cylinder_hit_normal(struct s_cylinder *this, t_point3 impact, int hit_side)
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
	t_point3	impact;
	t_vec		surface_normal;
	t_ray		impact_normal;
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
