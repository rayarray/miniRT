/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:43:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 21:02:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape_cylinder.h"
#include "rt_validations.h"
#include "rt_typedef.h"

/*
# Cylinder: type identifer | xyz coordinates | vector of axis of cylinder | diameter | height | colors (RGB)
cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
*/

int	cylinder_ctor(struct s_cylinder *cylinder, t_point loc, t_vec axis,
	double *dimensions, t_color color)
{
	shape_ctor(&cylinder->base, e_CYLINDER, loc);
	if (!is_unitvec(axis))
		return (1);
	cylinder->diameter = dimensions[e_DIAMETER];
	cylinder->height = dimensions[e_HEIGHT];
	cylinder->axis = axis;
	cylinder->color = color;
	return (0);
}