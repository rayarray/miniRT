/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:39:10 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 00:36:55 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_plane.h"
#include "rt_validations.h"

int	plane_ctor(struct s_plane *plane, t_vec point, t_vec normal, t_color color)
{
	static const struct s_shape_vtable	vtable = {
			(void (*)(struct s_shape *this))plane_dtor,
			(t_color (*)(struct s_shape *this, struct s_scene *scene, t_ray ray))plane_hit_ray
		};

	shape_ctor(&plane->base, e_PLANE, point);
	plane->base.vtptr = &vtable;
	if (!is_unitvec(normal))
		return (1);
	plane->normal = normal;
	plane->color = color;
	return (0);
}

void	plane_dtor(struct s_plane *plane)
{
	_shape_base_dtor(&plane->base);
}

t_color	plane_hit_ray(struct s_plane *this, struct s_scene *scene, t_ray ray)
{
	t_color	color;

	(void)scene;
	(void)ray;
	(void)this;
	color = (t_color){0xFF, 0xFF, 0xFF, 0xFF};	// placeholder
	return (color);
}