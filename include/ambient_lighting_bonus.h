/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lighting_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:16 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_LIGHTING_BONUS_H
# define AMBIENT_LIGHTING_BONUS_H
# include "rt_typedef_bonus.h"

struct s_ambient_lighting
{
	double	light_ratio;
	t_color	color;
};

int	ambient_lighting_ctor(struct s_ambient_lighting *a_lt,
		double lighting_ratio, t_color color);

#endif