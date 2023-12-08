/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:06:28 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/08 15:22:34 by rleskine         ###   ########.fr       */
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

// samples_per_px: random samples per pixel
// max_depth: maximum number of ray bounces
typedef struct s_camera2 {
	double	aspect_ratio;
	int		img_width;
	int		img_height;
	int		samples_per_px;
	int		max_depth;		// not necessary here?
	double	h_fov;			// radians!

	t_vec	look_from;
	t_vec	look_at;
	t_vec	up;

	//double	defocus_angle;	// should not be necessary
	double	focus_dist;		// dist from camera lookfrom to plane of perfect focus (used or not?)
	t_ray	center;
	t_vec	pixel00_loc;
	t_vec	px_delta_u;
	t_vec	px_delta_v;
	t_vec	u;
	t_vec	v;
	t_vec	w;

	double	h;
	double	viewport_height;
	double	viewport_width;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	viewport_upleft;
}	t_camera2;

//t_vec	cameraUp(t_vec camera_dir);
//t_vec	cameraLeft(t_vec camera_dir);
//t_vec	vecXRotate(t_vec vector, double angle);
//t_vec	vecZRotate(t_vec vector, double angle);
int		camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov);

//t_camera	initCamera(mlx_image_t *image, int fov, void *scene, t_ray center);	// deprecated
//void		renderCamera(mlx_image_t *image, t_camera c);	// deprecated

t_camera2	initCamera(t_ray center, int width, int height, double fov);
t_ray		getRay(t_camera2 c, int i, int j);


#endif	/* CAMERA_H */
