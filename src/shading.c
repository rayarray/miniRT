/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:54 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/04 14:09:29 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shading.h"
#include "light.h"
#include "color.h"
#include "rt_math.h"
#include "rt_typedef.h"
#include "ambient_lighting.h"
#include "tracer.h"

t_color	apply_ambient(t_color color, struct s_ambient_lighting *ambience)
{
	return (color_fade_to(color, ambience->color, ambience->light_ratio));
}

t_color	facing_ratio(t_vec surface_normal, t_vec facing,
	t_color surface_color, t_color ambient_color)
{
	double	ratio;
	
	ratio = 1 + dot_product(surface_normal, facing);
	if (flessthan(ratio, 1))
		surface_color = color_fade_to(surface_color, ambient_color, ratio);
	return (surface_color);
}

#include <stdio.h>
t_color	diffuse_shading(struct s_scene *scene, t_vec surface_normal,
	t_point3 impact, t_color surface_color)	// surface_normal and impact could be combined into t_ray?
{
	t_color			color;
	t_vec			vL;
	double			 diffusely_reflected_light;
	struct s_light	*light;

	static double	highest_light = 0;	//debug
	(void)highest_light;

	color = surface_color;
	light = scene->lights;
	while (light != NULL)	// Multiple lights, bonus stuff
	{
		vL = vec_normalize(vec_sub(light->loc, impact));
		if (/* fgreaterthan(dot_product(surface_normal, vL), 0)	// Optimization
			&& */ (!collision_test(scene, (t_ray){impact, vL}, vec_length(vec_sub(impact, light->loc)))))	// Does this distinguish between the required shape and the others?
		{
			diffusely_reflected_light = light->brightness * fmax(0, dot_product(surface_normal, vL));	// use distance to factor brightness here?
/*  			if (fgreaterthan(diffusely_reflected_light, highest_light))	// debug
			{
				highest_light = diffusely_reflected_light;
				printf("impact %f,%f,%f vL %f,%f,%f\n", impact.x, impact.y, impact.z, vL.x, vL.y, vL.z);
				printf("L length %f\n", vec_length(vec_sub(impact, light->loc)));
		//			printf("impact %f,%f,%f light %f,%f,%f\n", impact.x, impact.y, impact.z, light->loc.x, light->loc.y, light->loc.z);
				printf("Normal %f,%f,%f\n", surface_normal.x, surface_normal.y, surface_normal.z);
				printf("dot_prod %f\n", dot_product(surface_normal, vL));
			}
 */			color = color_fade_to(surface_color, light->color, diffusely_reflected_light);
		}
		light = light->next;
	}
	return color;
}
