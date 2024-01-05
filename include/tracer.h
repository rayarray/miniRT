/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:55 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/04 19:57:01 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_H
# define TRACER_H
# define BOUNCE_LIMIT 1
# include "rt_typedef.h"
# include "scene.h"

t_color	cast_ray(struct s_scene *scene, t_ray ray, int bounces);

int		collision_test(struct s_scene *scene, t_ray ray, double length);

#endif	/* TRACER_H */