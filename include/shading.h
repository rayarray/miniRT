/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:31:29 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/21 22:46:50 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H
# include "rt_typedef.h"
# include "ambient_lighting.h"
# include "light.h"

t_color	apply_ambient(t_color color, struct s_ambient_lighting *ambience);
// Simple facing ratio shading but isn't required by the subject.
t_color	facing_ratio(t_vec surface_normal, t_vec facing,
	t_color color, t_color ambient);
t_color	diffuse_shading(struct s_light *lights, t_vec surface_normal,
	t_point3 impact, t_color surface_color);

#endif /* SHADING_H */
