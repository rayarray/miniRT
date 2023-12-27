/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:07 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/18 18:23:29 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CONE_H
# define SHAPE_CONE_H
# include "shape.h"
# include "rt_typedef.h"

typedef enum e_cone_dimension_index
{
	e_CONE_DIAMETER,
	e_CONE_HEIGHT
}	t_cone_dimension_index;

typedef enum e_cone_orientation_index
{
	e_CONE_LOCATION,
	e_CONE_AXIS
}	t_cone_orientation_index;

struct s_cone
{
	struct s_shape	base;
	t_vec			axis;
	double			diameter;
	double			height;
};

int		cone_ctor(struct s_cone *this, t_vec orientation[2],
			double dimensions[2], t_color color);

void	cone_dtor(struct s_cone *this);

double	cone_intersect_distance(struct s_cone *this, t_ray ray);

t_color	cone_intersect_color(struct s_cone *this,
			struct s_scene *scene, t_ray ray, int bounces);

#endif