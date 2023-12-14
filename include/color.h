/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:40 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/14 23:19:09 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "rt_typedef.h"

// Fades color by the extent of the intensity. 1 == no change, 0 fades to black
t_color	color_fade(t_color c, double intensity);

// Fades c1 to c2 by the extent of the intensity.
// 1 == no change, 0 == fade completely to c2
t_color	color_apply_light(t_color surface, t_color light, double intensity);

t_color	color_mix(t_color c1, t_color c2);

t_color	color_reflect_light(t_color surface, t_color light, double intensity);

#endif /* COLOR_H */
