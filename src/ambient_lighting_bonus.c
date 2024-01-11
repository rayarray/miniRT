/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lighting_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:54:34 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ambient_lighting_bonus.h"
#include "rt_validations_bonus.h"
#include "parser_bonus.h"

int	ambient_lighting_ctor(struct s_ambient_lighting *a_lt,
	double light_ratio, t_color color)
{
	if (!is_ratio(light_ratio))
		return (1);
	a_lt->light_ratio = light_ratio;
	a_lt->color = color;
	return (0);
}
