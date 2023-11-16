/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:12:00 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 17:03:15 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_SPHERE_H
# define SHAPE_SPHERE_H
# include "element.h"

struct s_sphere
{
	struct s_shape	base;
	t_vec			pos;
	double			diameter;
	t_color			color;
};

void	sphere_dtor(struct s_shape *shape);		//??

#endif