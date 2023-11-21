/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:54 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/21 22:49:48 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shading.h"
#include "light.h"
#include "color.h"
#include "rt_math.h"
#include "rt_typedef.h"
#include "ambient_lighting.h"

t_color	apply_ambient(t_color color, struct s_ambient_lighting *ambience)
{
	return (color_fade_to(color, ambience->color, ambience->light_ratio));
}

t_color	facing_ratio(t_vec surface_normal, t_vec facing,
	t_color surface_color, t_color ambient_color)
{
	double	ratio;
	
	ratio = 1 + dot_product(surface_normal, facing);
	if (ratio < 1)
		surface_color = color_fade_to(surface_color, ambient_color, ratio);
	return (surface_color);
}

t_color	diffuse_shading(struct s_light *lights, t_vec surface_normal,
	t_point3 impact, t_color surface_color)
{
	t_color	color;
	t_vec	vL;
	double diffusely_reflected_light;

	color = surface_color;
	while (lights != NULL)	// Multiple lights, bonus stuff
	{
		vL = vec_normalize(vec_sub(lights->loc, impact));
		diffusely_reflected_light = lights->brightness * fmax(0, dot_product(surface_normal, vL));	// use distance to factor brightness here?
		color = color_fade_to(surface_color, lights->color, diffusely_reflected_light);
		lights = lights->next;
	}
	return color;
}