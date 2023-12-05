/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/05 17:26:55 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "rt_math.h"

t_color	color_fade(t_color color, double factor)
{
	color.r = round(((double)color.r * factor));
	color.g = round(((double)color.g * factor));
	color.b = round(((double)color.b * factor));
	return (color);
}

t_color	color_fade_to(t_color color, t_color anothercolor, double factor)
{	// TODO better/more natural function for this
	if (fgreaterthan(factor, 1.0))
		factor = 1.0;
	color.r = round(((double)color.r * (1 - factor) + (double)anothercolor.r * factor));
	color.g = round(((double)color.g * (1 - factor) + (double)anothercolor.g * factor));
	color.b = round(((double)color.b * (1 - factor) + (double)anothercolor.b * factor));
	return (color);
}