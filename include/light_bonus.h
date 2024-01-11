/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:10:48 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_BONUS_H
# define LIGHT_BONUS_H
# include "rt_typedef_bonus.h"

struct s_light
{
	struct s_light	*next;
	t_vec			loc;
	double			brightness;
	t_color			color;
};

int		light_ctor(struct s_light *l, t_vec pos, double brightness, t_color c);

void	light_dtor(struct s_light **l);

#endif