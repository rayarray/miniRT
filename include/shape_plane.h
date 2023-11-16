/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:38:11 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 18:06:20 by tsankola         ###   ########.fr       */
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
	t_color			color;
};

int	plane_ctor(struct s_plane *plane, t_vec point, t_vec normal, t_color color);


#endif