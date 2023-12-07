/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/07 19:00:36 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "rt_math.h"

t_color	color_fade(t_color color, double intensity)
{
	color.r = round(((double)color.r * intensity));
	color.g = round(((double)color.g * intensity));
	color.b = round(((double)color.b * intensity));
	return (color);
}

t_color	color_apply_light(t_color color, t_color light, double brightness)
{
	if (fgreaterthan(brightness, 1.0))
		brightness = 1.0;
	color.r = round(((double)color.r * light.r * brightness) / 255);
	color.g = round(((double)color.g * light.g * brightness) / 255);
	color.b = round(((double)color.b * light.b * brightness) / 255);
	return (color);
}

t_color	color_fade_to(t_color color, t_color anothercolor, double intensity)
{	// TODO better/more natural function for this
	// TODO colorful lights are only for bonus part
	if (fgreaterthan(intensity, 1.0))
		intensity = 1.0;
	color.r = round(((double)color.r * (1 - intensity) + (double)anothercolor.r * intensity));
	color.g = round(((double)color.g * (1 - intensity) + (double)anothercolor.g * intensity));
	color.b = round(((double)color.b * (1 - intensity) + (double)anothercolor.b * intensity));
	return (color);
}
