/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:40 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/07 18:58:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# define COL_WHITE (t_color){.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF}
# define COL_BLACK (t_color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF}
# define COL_RED (t_color){.r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF}
# define COL_GREEN (t_color){.r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF}
# define COL_BLUE (t_color){.r = 0x00, .g = 0x00, .b = 0xFF, .a = 0xFF}
# define COL_BACKGROUND COL_BLACK
# include "rt_typedef.h"

// Fades color by the extent of the intensity. 1 == no change, 0 fades to black
t_color	color_fade(t_color color, double intensity);

// Fades color to anothercolor by the extent of the intensity. 1 == no change, 0 == fade completely to anothercolor
t_color	color_fade_to(t_color color, t_color anothercolor, double intensity);

#endif /* COLOR_H */
