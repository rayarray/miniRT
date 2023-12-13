/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:31:29 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/13 22:02:12 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H
# define DIFFUSE_COEFFICIENT 16.0
# define SPECULAR_COEFFICIENT 16.0
# define SPECULAR_POWER 16.0
# include "rt_typedef.h"
# include "ambient_lighting.h"
# include "scene.h"

t_color	apply_ambient(t_color color, struct s_ambient_lighting *ambience);
t_color	facing_ratio(t_vec surface_normal, t_vec facing,
			t_color color, t_color ambient);	// Simple facing ratio shading but this isn't required by the subject.
t_color	diffuse_shading(struct s_scene *scene, t_ray impact_normal,
			t_color color);
t_color	specular_lighting(struct s_scene *scene, t_ray impact_normal,
			t_ray spectator_ray, t_color color);
t_color	specular_reflection(struct s_scene *scene, t_ray impact_norm,
			t_ray eye_ray, t_color color, int bounces);

#endif /* SHADING_H */
