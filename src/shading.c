/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:54 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/09 19:45:43 by tsankola         ###   ########.fr       */
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
	return (color_apply_ambient(color, ambience->color, ambience->light_ratio));
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
	t_color color)
{
	t_vec			v_l;
	double			diffusely_reflected_light;
	struct s_light	*light;

	light = scene->lights;
	while (light != NULL)
	{
		v_l = vec_normalize(vec_sub(light->loc, impact_normal.origin));
		if (!collision_test(scene, (t_ray){impact_normal.origin, v_l},
			vec_length(vec_sub(impact_normal.origin, light->loc))))
		{
			// TODO use distance to factor brightness?
			diffusely_reflected_light = DIFFUSE_COEFFICIENT * light->brightness
				* fmax(0, dot_product(impact_normal.destination, v_l));
			color = color_fade_to(color, light->color,
					diffusely_reflected_light);
		}
		light = light->next;
	}
	return (color);
}

t_color	specular_lighting(struct s_scene *scene, t_ray impact_norm,
	t_ray spectator_ray, t_color color)
{
	t_vec			v_l;
	t_vec			v_r;
	t_vec			v_e;
	struct s_light	*light;
	double			specular_reflected_light;

	light = scene->lights;
	while (light != NULL)
	{
		v_l = vec_normalize(vec_sub(light->loc, impact_norm.origin));
		if ((!collision_test(scene, (t_ray){impact_norm.origin, v_l},
				vec_length(vec_sub(impact_norm.origin, light->loc)))))
		{
			v_r = vec_sub(vec_scal_mul(impact_norm.destination,
						(2 * dot_product(impact_norm.destination, v_l))), v_l);
			v_e = vec_normalize(vec_sub(spectator_ray.origin,
						impact_norm.origin));
			// TODO Factor distance to brightness?
			specular_reflected_light = SPECULAR_COEFFICIENT * light->brightness
				* pow(fmax(0, dot_product(v_r, v_e)), 16);
			color = color_fade_to(color, light->color,
					specular_reflected_light);
		}
		light = light->next;
	}
	return (color);
}
