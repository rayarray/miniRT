/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:54 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/14 16:05:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shading.h"
#include "light.h"
#include "color.h"
#include "rt_math.h"
#include "tracer.h"

t_color	apply_ambient(struct s_ambient_lighting *ambience)
{
	return (color_fade(ambience->color, ambience->light_ratio));
}

t_color	facing_ratio(t_vec surface_normal, t_vec facing,
	t_color surface_color, t_color ambient_color)
{
	double	ratio;

	ratio = 1 + dot_product(surface_normal, facing);
	if (flessthan(ratio, 1))
		surface_color = color_apply_light(surface_color, ambient_color, ratio);
	return (surface_color);
}

t_color	diffuse_shading(struct s_scene *scene, t_ray impact_norm,
	t_color color)
{
	t_vec			v_l;
	double			intensity;
	struct s_light	*light;

	light = scene->lights;
	while (light != NULL)
	{
		v_l = vec_normalize(vec_sub(light->loc, impact_norm.origin));
		if (!collision_test(scene, (t_ray){impact_norm.origin, v_l},
			vec_length(vec_sub(impact_norm.origin, light->loc))))
		{
			intensity = DIFFUSE_COEFFICIENT * light->brightness
				* fmax(0, dot_product(impact_norm.destination, v_l));
			intensity /= pow(vec_length(
					vec_sub(light->loc, impact_norm.origin)), 2);
			color = color_apply_light(color, light->color, intensity);
		}
		light = light->next;
	}
	return (color);
}

t_color	specular_lighting(struct s_scene *scene, t_ray impact_norm,
	t_ray eye_ray, t_color color)
{
	t_vec			v_l;
	t_vec			v_r;
	t_vec			v_e;
	struct s_light	*light;
	double			intensity;
	
	light = scene->lights;
	v_e = vec_normalize(vec_sub(eye_ray.origin, impact_norm.origin));
	while (light != NULL)
	{
		v_l = vec_normalize(vec_sub(light->loc, impact_norm.origin));
		if ((!collision_test(scene, (t_ray){impact_norm.origin, v_l},
				vec_length(vec_sub(impact_norm.origin, light->loc)))))
		{
			v_r = vec_sub(vec_scal_mul(impact_norm.destination,
						(2 * dot_product(impact_norm.destination, v_l))), v_l);
			intensity = SPECULAR_COEFFICIENT * light->brightness
				* pow(fmax(0, dot_product(v_r, v_e)), SPECULAR_POWER);
			intensity /= pow(vec_length(
					vec_sub(light->loc, impact_norm.origin)), 2);
			color = color_apply_light(color, light->color, intensity);
		}
		light = light->next;
	}
	return (color);
}

t_color	specular_reflection(struct s_scene *scene, t_ray impact_norm,
	t_ray eye_ray, t_color color, int bounces)
{
	t_vec			v_s;
	t_vec			v_e;
	struct s_shape	*shape;
	double			intensity;
	t_color			refl_col;
	
	if (bounces <= 0)
		return color;
	shape = scene->shapes;
	v_e = vec_normalize(vec_sub(eye_ray.origin, impact_norm.origin));
	v_s = vec_sub(vec_scal_mul(impact_norm.destination, 2 * dot_product(v_e, impact_norm.destination)
		/ dot_product(impact_norm.destination, impact_norm.destination)), v_e);
	refl_col = cast_ray(scene, (t_ray){impact_norm.origin, v_s}, bounces);
	intensity = 0.5;	// TODO each shape should have their own reflection factor or something
	color = color_apply_light(color, refl_col, intensity);
	shape = shape->next;
	return (color);
}
