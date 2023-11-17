/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 00:18:55 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CYLINDER_H
# define SHAPE_CYLINDER_H
# include "rt_typedef.h"
# include "shape.h"

typedef enum e_cylinder_dimension_index
{
	e_DIAMETER,
	e_HEIGHT
}	t_cylinder_dimension_index;

struct s_cylinder
{
	struct s_shape	base;
	t_vec			axis;
	double			diameter;
	double			height;
	t_color			color;
};

int	cylinder_ctor(struct s_cylinder *this, t_point loc, t_vec axis,
	double *dimensions, t_color color);	// TODO reduce parameters by one. Either combine loc and axis (technically a type error), or just edit the values directly, I dunno.

void	cylinder_dtor(struct s_cylinder *this);

t_color	cylinder_hit_ray(struct s_cylinder *this, struct s_scene *scene, t_ray ray);

#endif