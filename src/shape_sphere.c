/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:16:05 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 23:29:06 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_sphere.h"

int	sphere_ctor(struct s_sphere *this, t_vec loc, double diameter, t_color color)
{
	static const struct s_shape_vtable	sphere_vtable = {
			(void (*)(struct s_shape *this))sphere_dtor,
			(t_color (*)(struct s_shape *this, struct s_scene *scene, t_ray ray))sphere_hit_ray
		};

	shape_ctor(&this->base, e_SPHERE, loc);
	this->base.vtptr = &sphere_vtable;
	this->color = color;
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
	color = this->color;
	return (color);
}