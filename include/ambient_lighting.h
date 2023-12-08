/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lighting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:16 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 15:49:18 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_LIGHTING_H
# define AMBIENT_LIGHTING_H
# include "rt_typedef.h"

struct s_ambient_lighting
{
	double	light_ratio;
	t_color	color;
};

int	ambient_lighting_ctor(struct s_ambient_lighting *a_lt,
		double lighting_ratio, t_color color);

#endif