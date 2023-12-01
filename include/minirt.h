/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:02:44 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/27 04:00:59 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define TITLE "miniRT"
# define WIDTH	800
# define HEIGHT	512
# define IMAGE_WIDTH WIDTH
# define IMAGE_HEIGHT HEIGHT
# include "scene.h"
# include "MLX42.h"

struct s_minirt
{
	struct s_scene	*scene;
	mlx_t			*mlx;
	mlx_image_t		*image;
};

void	render(struct s_scene *scene, mlx_image_t *image);

// hooks.c
void	minirt_resize_hook(int32_t width, int32_t height, struct s_minirt *minirt);
void	minirt_loop_hook(struct s_minirt *minirt);
void	minirt_key_hook(mlx_key_data_t keydata, struct s_minirt *minirt);
void	minirt_close_hook(struct s_minirt *minirt);

#endif