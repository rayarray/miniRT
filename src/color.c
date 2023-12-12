/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:30 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/12 19:53:46 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"
#include "rt_math.h"

t_color	color_fade(t_color c, double intensity)
{
	c.r = round(((double)c.r * intensity));
	c.g = round(((double)c.g * intensity));
	c.b = round(((double)c.b * intensity));
	return (c);
}

t_color	color_apply_ambient(t_color c, t_color ambient, double brightness)
{
	if (fgreaterthan(brightness, 1.0))
		brightness = 1.0;
	if (flessthan(brightness, 0.01))
		brightness = 0.01;
	c.r = round(((double)c.r * (ambient.r * brightness)) / 255);
	c.g = round(((double)c.g * (ambient.g * brightness)) / 255);
	c.b = round(((double)c.b * (ambient.b * brightness)) / 255);
	return (c);
}

t_color	color_fade_to(t_color c1, t_color c2, double intensity)
{
	if (fgreaterthan(intensity, 1.0))
		intensity = 1.0;
	c1.r = round(((double)c1.r * (1 - intensity) + (double)c2.r * intensity));
	c1.g = round(((double)c1.g * (1 - intensity) + (double)c2.g * intensity));
	c1.b = round(((double)c1.b * (1 - intensity) + (double)c2.b * intensity));
	return (c1);
}
