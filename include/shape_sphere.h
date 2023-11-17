/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:12:00 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 23:43:45 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_SPHERE_H
# define SHAPE_SPHERE_H
# include "shape.h"
# include "rt_typedef.h"

struct s_sphere
{
	struct s_shape	base;
	t_vec			loc;
	double			diameter;
	t_color			color;
};

int		sphere_ctor(struct s_sphere *this, t_vec loc, double diameter, t_color color);

void		sphere_dtor(struct s_sphere *this);

t_color		sphere_hit_ray(struct s_sphere *this, struct s_scene *scene, t_ray ray);

#endif