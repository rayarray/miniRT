/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:06:28 by rleskine          #+#    #+#             */
/*   Updated: 2023/10/26 16:03:23 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "MLX42.h"
# include "ray.h"

typedef struct s_camera {
	int		fov;
	t_ray	center;
	void	*scene;
	double	focal_length;
	int		image_width;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	viewport_uv_half;
	t_vec	pixel_delta_u;
	t_vec	pixel_delta_v;
	t_vec	viewport_upper_left;
	t_vec	pixel00_loc;
}	t_camera;

t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center);
void		renderCamera(mlx_image_t *image, t_camera c);

#endif	/* CAMERA_H */
