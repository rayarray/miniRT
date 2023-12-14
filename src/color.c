/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/14 16:25:11 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "rt_math.h"

static t_color	color_clamped(int r, int g, int b) {
	double	scale;
	int max_component;

	max_component = imax(imax(r,g),b);
	if (max_component > 255) {
		scale = (double)max_component / 255;
		r = round((double)r / scale);
		g = round((double)g / scale);
		b = round((double)b / scale);
	}
	return ((t_color){r, g, b, 0xFF});
}

t_color	color_fade(t_color c, double intensity)
{
	c.r = round(((double)c.r * intensity));
	c.g = round(((double)c.g * intensity));
	c.b = round(((double)c.b * intensity));
	return (c);
}

t_color	color_apply_light(t_color surface, t_color light, double intensity)
{
	int	r;
	int	g;
	int	b;

	if (fgreaterthan(intensity, 1.0))
		intensity = 1.0;
	r = surface.r + round((double)light.r * intensity);
	g = surface.g + round((double)light.g * intensity);
	b = surface.b + round((double)light.b * intensity);
	return color_clamped(r,g,b);
}

t_color	color_mix(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r * c2.r / 255,		// Rounding errors here?
		c1.g * c2.g / 255,
		c1.b * c2.b / 255,
		0xFF
	});
}
