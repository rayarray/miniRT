/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_cylinder_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:05:17 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder_bonus.h"
#include "rt_validations_bonus.h"
#include "rt_typedef_bonus.h"

int	infinite_cylinder_intersect(struct s_cylinder *this, t_ray ray,
			t_surface_hits *hit, t_cylinder_products var)
{
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
	if (!fleq(var.d, this->radius))
		return (0);
	var.ov = cross_product(var.rc, this->axis);
	var.t = -dot_product(var.ov, var.nv) / var.ln;
	var.ov = vec_normalize(cross_product(var.nv, this->axis));
	var.s = fabs(sqrt(this->rad2 - var.d * var.d)
			/ dot_product(ray.dir, var.ov));
	hit->in = var.t - var.s;
	hit->out = var.t + var.s;
	return (1);
}

int	cylinder_clip_cap2(t_surface_hits *hit, double dc, double dw)
{
	double	t;

	t = -dw / dc;
	if (fgeq(dc, 0.0))
	{
		if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
		{
			hit->out = t;
			hit->surfout = hit->pass + 1;
		}
		if (flessthan(t, hit->in))
			return (0);
	}
	else
	{
		if (fgreaterthan(t, hit->in) && flessthan(t, hit->out))
		{
			hit->in = t;
			hit->surfin = hit->pass + 1;
		}
		if (fgreaterthan(t, hit->out))
			return (0);
	}
	return (1);
}

double	cylinder_clip_cap(struct s_cylinder *this, t_ray ray,
		t_surface_hits *hit, t_plane_eq pln)
{
	double	dc;
	double	dw;

	dc = pln.a * ray.dir.x + pln.b * ray.dir.y + pln.c * ray.dir.z;
	dw = pln.a * ray.loc.x + pln.b * ray.loc.y + pln.c * ray.loc.z + pln.d;
	if (feq(dc, 0.0) && fgeq(dw, 0.0))
		return (INFINITY);
	else if (!feq(dc, 0.0))
	{
		if (cylinder_clip_cap2(hit, dc, dw) == 0)
			return (INFINITY);
	}
	if (++hit->pass == 1)
		return (cylinder_clip_cap(this, ray, hit, this->top));
	if ((hit->surfin == CYL_BOT && hit->surfout == CYL_TOP)
		|| (hit->surfin == CYL_TOP && hit->surfout == CYL_BOT))
		return (fmin(hit->in, hit->out));
	else if (hit->in < hit->out)
		return (hit->in);
	else
		return (INFINITY);
}

t_surface_hits	cylinder_intersect_hits(struct s_cylinder *this, t_ray ray)
{
	t_surface_hits		hits;
	t_vec				origo;
	t_cylinder_products	var;

	ft_bzero(&hits, sizeof(t_surface_hits));
	ft_bzero(&var, sizeof(t_cylinder_products));
	if (!infinite_cylinder_intersect(this, ray, &hits, var) && --hits.pass)
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
		dsq = dot_product(pd, pd) - ((dot * dot)
				/ (this->height * this->height));
		if (fgreaterthan(dsq, this->rad2 * 4))
			return (0);
		else
			return (1);
	}
}
