/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_ambient_lighting.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:16 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 22:47:27 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEM_AMBIENT_LIGHTING_H
# define ELEM_AMBIENT_LIGHTING_H
# include "rt_typedef.h"
# include "element.h"

struct s_ambient_lighting
{
	struct s_elem	base;
	double			lighting_ratio;
	t_color			color;
};

int	ambient_lighting_ctor(struct s_ambient_lighting *a_lt, 
	double lighting_ratio, t_color color)
{
	a_lt->base.type = e_AMBIENT_LIGHTING;
	a_lt->lighting_ratio = lighting_ratio;
	a_lt->color = color;
}

#endif