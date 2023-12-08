/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:55 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/08 16:09:48 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_H
# define TRACER_H
# include "rt_typedef.h"
# include "scene.h"

t_color	trace_ray(struct s_scene *scene, uint32_t width, uint32_t height,
			t_pixel	pixel_point);

int		collision_test(struct s_scene *scene, t_ray ray, double length);

#endif	/* TRACER_H */