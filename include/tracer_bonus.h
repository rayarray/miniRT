/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:00:55 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_BONUS_H
# define TRACER_BONUS_H
# define BOUNCE_LIMIT 1
# include "rt_typedef_bonus.h"
# include "scene_bonus.h"

t_color	cast_ray(struct s_scene *scene, t_ray ray, int bounces);
int		collision_test(struct s_scene *scene, t_ray ray, double length);

#endif	/* TRACER_BONUS_H */