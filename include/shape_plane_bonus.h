/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:38:11 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_PLANE_H
# define SHAPE_PLANE_H
# include "rt_typedef_bonus.h"
# include "shape_bonus.h"

struct s_plane
{
	struct s_shape	base;
	t_vec			point;
	t_vec			normal;
};

int		plane_ctor(struct s_plane *p, t_vec point, t_vec normal,
			t_color color);
void	plane_dtor(struct s_plane *p);
double	plane_intersect_distance(struct s_plane *p, t_ray ray);
t_color	plane_intersect_color(struct s_plane *p, struct s_scene *scene,
			t_ray ray, int bounces);

#endif