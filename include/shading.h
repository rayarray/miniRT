/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:31:29 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/04 15:57:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H
# define SPECULAR_COEFFICIENT 1.5
# define DIFFUSE_COEFFICIENT 1.0
# define SHADOW_COEFFICIENT 0.3
# include "rt_typedef.h"
# include "ambient_lighting.h"
# include "light.h"
# include "scene.h"

t_color	apply_ambient(t_color color, struct s_ambient_lighting *ambience);
t_color	facing_ratio(t_vec surface_normal, t_vec facing,
	t_color color, t_color ambient);	// Simple facing ratio shading but this isn't required by the subject.
t_color	diffuse_shading(struct s_scene *scene, t_ray impact_normal,
	t_color surface_color);
t_color	specular_lighting(struct s_scene *scene, t_ray impact_normal,
	t_ray spectator_ray, t_color surface_color);

#endif /* SHADING_H */
