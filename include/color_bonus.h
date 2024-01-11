/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:40 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "rt_typedef_bonus.h"

// Fades color by the extent of the intensity. 1 == no change, 0 fades to black
t_color	color_fade(t_color c, double intensity);

// Brightens surface color with the light to the extent of the intensity.
t_color	color_apply_light(t_color surface, t_color light, double intensity);

// Calculates the average between the two colors
t_color	color_mix(t_color c1, t_color c2);

// Replaces the surface color by light to the extent of intensity.
t_color	color_reflect_light(t_color surface, t_color light, double intensity);

#endif /* COLOR_H */
