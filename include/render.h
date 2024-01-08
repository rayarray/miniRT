/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:32 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/08 14:03:41 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <math.h>
# include "MLX42.h"
# include "color.h"
# include "camera.h"
# include "scene.h"
# include "tracer.h"
# include "rt_typedef.h"

void	render(struct s_scene *scene, mlx_image_t *image);
void	debug_ray(struct s_scene *scene, mlx_image_t *image, uint32_t x, uint32_t y);

#endif	/* RENDER_H */
