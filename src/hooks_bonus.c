/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:06:19 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:03:14 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "MLX42.h"

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
