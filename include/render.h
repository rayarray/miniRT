/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:32 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/12 00:14:57 by rleskine         ###   ########.fr       */
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

#endif	/* RENDER_H */
