/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:35 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 14:54:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "rt_typedef.h"

void	shape_dtor(struct s_shape *this)
{
	this->vtptr->shape_dtor(this);
}

double	intersect_distance(struct s_shape *this, t_ray ray)
{
	return (this->vtptr->intersect_distance(this, ray));
}

t_color	intersect_color(struct s_shape *this, struct s_scene *scene, t_ray ray,
			int bounces)
{
	return (this->vtptr->intersect_color(this, scene, ray, bounces - 1));
}
