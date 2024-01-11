/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:06:28 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 15:13:35 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "MLX42.h"
# include "rt_typedef.h"

typedef struct s_camera
{
	t_point3	loc;
	t_vec		dir;
	int			fov;			// perhaps fov could be saved as radians?
}	t_camera;

// samples_per_px: random samples per pixel
// max_depth: maximum number of ray bounces
typedef struct s_camera2
{
	double	aspect_ratio;
	int		img_width;
	int		img_height;
	int		samples_per_px;	// not used currently
	int		max_depth;		// not used currently
	double	h_fov;			// radians!
	t_vec	look_from;
	t_vec	look_at;
	t_vec	up;
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

int			camera_ctor(struct s_camera *c, t_point3 loc, t_vec dir, int fov);
t_camera2	init_camera(t_camera2 cam, int width, int height, double fov);
t_ray		get_ray(t_camera2 c, int i, int j);

#endif	/* CAMERA_H */
