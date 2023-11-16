/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:10:48 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 18:09:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "rt_typedef.h"

struct s_light
{
	t_vec			pos;
	double			brightness;
	t_color			color;
};

int		light_ctor(struct s_light *l, t_vec pos, double brightness, t_color color);

void	light_dtor(struct s_light *l);

#endif