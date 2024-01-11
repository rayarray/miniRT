/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:32 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H
# include <math.h>
# include "MLX42.h"
# include "color_bonus.h"
# include "camera_bonus.h"
# include "scene_bonus.h"
# include "tracer_bonus.h"
# include "rt_typedef_bonus.h"

void	render(struct s_scene *scene, mlx_image_t *image);

#endif	/* RENDER_BONUS_H */
