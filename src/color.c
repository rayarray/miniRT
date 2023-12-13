/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/13 21:41:29 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "rt_math.h"

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int imin(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

t_color	color_difference(t_color c1, t_color c2)
{
	t_color	retcol;

	retcol.r = imax(c1.r, c2.r) - imin(c1.r, c2.r);
	retcol.g = imax(c1.g, c2.g) - imin(c1.g, c2.g);
	retcol.b = imax(c1.b, c2.b) - imin(c1.b, c2.b);
	return (retcol);
}

t_color	color_fade(t_color c, double intensity)
{
	c.r = round(((double)c.r * intensity));
	c.g = round(((double)c.g * intensity));
	c.b = round(((double)c.b * intensity));
	return (c);
}

t_color	invert_color(t_color c)
{
	c.r = c.r ^ 255;
	c.g = c.g ^ 255;
	c.b = c.b ^ 255;
	return (c);
}

t_color	color_apply_ambient(t_color surface, t_color ambient, double brightness)
{
	t_color	color_diff;

	if (fgreaterthan(brightness, 1.0))
		brightness = 1.0;
	if (flessthan(brightness, 0.01))
		brightness = 0.01;
	color_diff = color_difference(surface, ambient);
	color_diff.r *= brightness;
	color_diff.g *= brightness;
	color_diff.b *= brightness;
	surface.r = round(((double)surface.r * (ambient.r * brightness)) / 255);
	surface.g = round(((double)surface.g * (ambient.g * brightness)) / 255);
	surface.b = round(((double)surface.b * (ambient.b * brightness)) / 255);
//	surface.r += color_diff.r;
//	surface.g += color_diff.g;
//	surface.b += color_diff.b;
//	return (surface);
	return (surface);
}

t_color	color_apply_light(t_color surface, t_color light, double intensity)
{
	if (fgreaterthan(intensity, 1.0))
		intensity = 1.0;
	surface.r = round(((double)surface.r * (1 - intensity) + (double)light.r * intensity));
	surface.g = round(((double)surface.g * (1 - intensity) + (double)light.g * intensity));
	surface.b = round(((double)surface.b * (1 - intensity) + (double)light.b * intensity));
//	int	max_surface = max(max(surface.r, surface.g), surface.b);
//	int	min_surface = min(min(surface.r, surface.g), surface.b);
	//surface.r = round(((double)surface.r * (light.r * intensity)) / 255);
	//surface.g = round(((double)surface.g * (light.g * intensity)) / 255);
	//surface.b = round(((double)surface.b * (light.b * intensity)) / 255);
	return (surface);
}
