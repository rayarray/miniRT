/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:06:28 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/25 04:27:54 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "MLX42.h"
# include "rt_typedef.h"

typedef struct s_camera {
	t_point3	loc;
	t_vec		dir;
	int			fov;			// perhaps fov could be saved as radians?
}	t_camera;

int	camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov);

t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center);
void		renderCamera(mlx_image_t *image, t_camera c);

#endif	/* CAMERA_H */
