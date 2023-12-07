/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:54 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/07 18:32:14 by tsankola         ###   ########.fr       */
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

#include <stdio.h>

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

t_color	diffuse_shading(struct s_scene *scene, t_ray impact_normal,
	t_color surface_color)	// surface_normal and impact could be combined into t_ray?
{
	t_color			color;
	t_vec			vL;
	double			diffusely_reflected_light;
	struct s_light	*light;

	color = surface_color;
	light = scene->lights;
	while (light != NULL)
	{
		vL = vec_normalize(vec_sub(light->loc, impact_normal.origin));
		if (!collision_test(scene, (t_ray){impact_normal.origin, vL}, vec_length(vec_sub(impact_normal.origin, light->loc))))	// Does this distinguish between the required shape and the others?
		{
//			diffusely_reflected_light = DIFFUSE_COEFFICIENT * light->brightness * fmax(0, dot_product(impact_normal.destination, vL));	// use distance to factor brightness here?
			diffusely_reflected_light = DIFFUSE_COEFFICIENT * light->brightness * fabs(dot_product(impact_normal.destination, vL));		// TODO test this. This was changed to incorporate plane, not sure if it works well with every shape
//			printf("%f\n", diffusely_reflected_light);
//			getchar();
			color = color_fade_to(surface_color, light->color, diffusely_reflected_light);
		}
		light = light->next;
	}
	return (color);
}

t_color	specular_lighting(struct s_scene *scene, t_ray impact_normal,
	t_ray spectator_ray, t_color surface_color)
{
	t_color			color;
	t_vec			vL;
	t_vec			vR;
	t_vec			vE;
	struct s_light	*light;
	double			specular_reflected_light;
	double			intensity;

	color = surface_color;
	light = scene->lights;
	while (light != NULL)
	{
		vL = vec_normalize(vec_sub(light->loc, impact_normal.origin));
		if (/* fgreaterthan(dot_product(surface_normal, vL), 0)	// Optimization
			&& */ (!collision_test(scene, (t_ray){impact_normal.origin, vL}, vec_length(vec_sub(impact_normal.origin, light->loc)))))
		{
			vR = vec_sub(vec_scal_mul(impact_normal.destination, (2 * dot_product(impact_normal.destination, vL))), vL);
			vE = vec_normalize(vec_sub(spectator_ray.origin, impact_normal.origin));
			intensity = 1.0 / (4 * M_PI * vec_length(vec_sub(light->loc, impact_normal.origin)));	// distance factor
			intensity = 1.0;	// The formula above doesn't seem to provide nice results
			specular_reflected_light = SPECULAR_COEFFICIENT * intensity * light->brightness * pow(fmax(0, dot_product(vR, vE)), 16);
			color = color_fade_to(surface_color, light->color, specular_reflected_light);
		}
//	TODO Shadows?
//		else
//			color = color_fade_to(surface_color, COL_BLACK, SHADOW_COEFFICIENT * light->brightness);
		light = light->next;
	}
	return (color);
}