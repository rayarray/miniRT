/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:55 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/18 22:31:52 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_H
# define TRACER_H

# include "camera.h"
# include "rt_typedef.h"
# include "scene.h"

uint32_t	rayColor(t_camera c, t_ray ray);

t_color	trace_ray(struct s_scene *scene, mlx_image_t *image,
	uint32_t x, uint32_t y);

#endif	/* TRACER_H */