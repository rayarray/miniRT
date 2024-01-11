/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:12:00 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_SPHERE_BONUS_H
# define SHAPE_SPHERE_BONUS_H
# include "shape_bonus.h"
# include "rt_typedef_bonus.h"

struct s_sphere
{
	struct s_shape	base;
	t_vec			loc;
	double			diameter;
};

int		sphere_ctor(struct s_sphere *s, t_vec loc, double diameter,
			t_color color);
void	sphere_dtor(struct s_sphere *s);
double	sphere_intersect_distance(struct s_sphere *s, t_ray ray);
t_color	sphere_intersect_color(struct s_sphere *s, struct s_scene *scene,
			t_ray ray, int bounces);

#endif