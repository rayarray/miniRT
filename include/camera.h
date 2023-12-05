/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:06:28 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/05 16:33:39 by rleskine         ###   ########.fr       */
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

// typedef struct s_camera {
// 	int		fov;
// 	t_ray	center;
// 	void	*scene;
// 	double	focal_length;
// 	int		image_width;
// 	double	aspect_ratio;
// 	double	viewport_height;
// 	double	viewport_width;
// 	t_vec	viewport_u;
// 	t_vec	viewport_v;
// 	t_vec	viewport_uv_half;
// 	t_vec	pixel_delta_u;
// 	t_vec	pixel_delta_v;
// 	t_vec	viewport_upper_left;
// 	t_vec	pixel00_loc;
// }	t_camera;

t_vec	cameraUp(t_vec camera_dir);
t_vec	cameraLeft(t_vec camera_dir);
t_vec	vecXRotate(t_vec vector, double angle);
t_vec	vecZRotate(t_vec vector, double angle);
int		camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov);

t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center);	// deprecated
void		renderCamera(mlx_image_t *image, t_camera c);	// deprecated

#endif	/* CAMERA_H */
