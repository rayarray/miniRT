/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:06:19 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/08 14:48:41 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"

// debug includes
#include <stdio.h> // remove / debug
#include "scene.h"
#include "shape.h"
#include "tracer.h"
#include "render.h"

void	minirt_resize_hook(int32_t width, int32_t height,
	struct s_minirt *minirt)
{
	mlx_resize_image(minirt->image, width, height);
}

void	minirt_loop_hook(struct s_minirt *minirt)
{
	static unsigned int	renderdone;

	if (renderdone != minirt->image->width + minirt->image->height)
	{
		render(minirt->scene, minirt->image);
		renderdone = minirt->image->width + minirt->image->height;
	}
	//mlx_close_window(minirt->mlx); // draw and then close
}

void	minirt_key_hook(mlx_key_data_t keydata, struct s_minirt *minirt)
{
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(minirt->mlx);
}

void	minirt_close_hook(struct s_minirt *minirt)
{
	mlx_close_window(minirt->mlx);
}

void	minirt_mouse_cursor_hook(double x, double y, void *param)
{
	struct s_minirt	*data;

	data = param;
	debug_ray(data->scene, data->image, x, y);
}

void	minirt_mouse_button_hook(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
{
	struct s_minirt	*data;

	(void)modifier;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		data = param;
		render(data->scene, data->image);
	}
}

// void	minirt_mouse_button_hook(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
// {
// 	int32_t	x;
// 	int32_t	y;
// 	t_camera2	cam;
// 	t_ray		camray;
// 	t_color	col;
// 	struct s_minirt	*data;

// 	data = param;
// 	(void)modifier;
// 	(void)param;
// 	(void)key;
// 	if ((action == MLX_PRESS || action == MLX_REPEAT))
// 	{
// 		mlx_get_mouse_pos(((struct s_minirt *)param)->mlx, &x, &y);
// 		printf("mouse left pressed on x:%d y:%d\n", x, y);
// 		cam = initCamera((t_ray){data->scene->camera->loc, data->scene->camera->dir}, data->image->width,
// 			data->image->height, (M_PI * data->scene->camera->fov) / 180);
// 		camray.loc = data->scene->camera->loc;
// 		camray.dir = unitVector(vecAdd(getRay(cam, x, y), data->scene->camera->dir));
// 		vecPrint("cam.loc", camray.loc, 0);
// 		vecPrint("cam.dir", camray.dir, 1);
// 		col = cast_ray(data->scene, camray, 7357);
// 		mlx_put_pixel(data->image, x, y, coltouint32_t(col));
// 	}
// }

//void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param)
//void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
