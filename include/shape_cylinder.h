/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 18:06:22 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CYLINDER_H
# define SHAPE_CYLINDER_H
# include "rt_typedef.h"
# include "shape.h"

struct s_cylinder
{
	struct s_shape	base;
	t_vec			pos;
	t_vec			axis;
	double			diameter;
	double			height;
	t_color			color;
};

int	cylinder_ctor(struct s_cylinder *cylinder, t_vec point, t_vec normal, t_color color);


#endif