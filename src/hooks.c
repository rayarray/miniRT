/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:06:19 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/21 18:16:00 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"

void	minirt_resize_hook(int32_t width, int32_t height, struct s_minirt *minirt)
{
	mlx_resize_image(minirt->image, width, height);
}

void	minirt_loop_hook(struct s_minirt *minirt)
{
	render(minirt->scene, minirt->image);
}

void	minirt_key_hook(mlx_key_data_t keydata, struct s_minirt *minirt)
{
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(minirt->mlx);
	}
}