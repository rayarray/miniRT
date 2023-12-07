/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/07 19:47:14 by tsankola         ###   ########.fr       */
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

t_color	color_apply_ambient(t_color color, t_color ambient, double brightness)
{
	if (fgreaterthan(brightness, 1.0))
		brightness = 1.0;
	color.r = round(((double)color.r * (ambient.r * brightness)) / 255);
	color.g = round(((double)color.g * (ambient.g * brightness)) / 255);
	color.b = round(((double)color.b * (ambient.b * brightness)) / 255);
	return (color);
}

t_color	color_fade_to(t_color c1, t_color c2, double intensity)
{	// TODO better/more natural function for this
	// TODO colorful lights are only for bonus part
	if (fgreaterthan(intensity, 1.0))
		intensity = 1.0;
	c1.r = round(((double)c1.r * (1 - intensity) + (double)c2.r * intensity));
	c1.g = round(((double)c1.g * (1 - intensity) + (double)c2.g * intensity));
	c1.b = round(((double)c1.b * (1 - intensity) + (double)c2.b * intensity));
	return (c1);
}
