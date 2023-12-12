/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:54:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 14:47:03 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ambient_lighting.h"
#include "rt_validations.h"
#include "parser.h"

int	ambient_lighting_ctor(struct s_ambient_lighting *a_lt,
	double light_ratio, t_color color)
{
	if (!is_ratio(light_ratio))
		return (1);
	a_lt->light_ratio = light_ratio;
	a_lt->color = color;
	return (0);
}
