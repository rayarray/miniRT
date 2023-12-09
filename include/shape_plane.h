/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:38:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/09 20:33:25 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_PLANE_H
# define SHAPE_PLANE_H
# include "rt_typedef.h"
# include "shape.h"

struct s_plane
{
	struct s_shape	base;
	t_vec			point;
	t_vec			normal;
};

int		plane_ctor(struct s_plane *plane, t_vec point, t_vec normal,
			t_color color);

void	plane_dtor(struct s_plane *plane);

double	plane_intersect_distance(struct s_plane *this, t_ray ray);

t_color	plane_intersect_color(struct s_plane *this, struct s_scene *scene,
			t_ray ray, int bounces);

#endif