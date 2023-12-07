/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/07 17:19:33 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"
#include "minirt.h"
#include "vector.h"
#include "camera.h"
#include "parser.h"
#include "scene.h"
#include "tracer.h"

/* 
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(void *param)
{
	(void)param;
	for (int32_t i = 0; i < (int)image->width; ++i)
	{
		for (int32_t y = 0; y < (int)image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
	for (int32_t i = 0; i < (int)image->width; i++)
		mlx_put_pixel(image, 256, i, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
} */

static uint32_t	coltouint32_t(t_color col)
{
	uint32_t	ret;

	ret = 0;
	ret += col.r << 24;
	ret += col.g << 16;
	ret += col.b << 8;
	ret += col.a;
	return (ret);
}

void	render(struct s_scene *scene, mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;
	t_color		col;

	y = 0 - 1;
	while (++y < image->height)
	{
		x = 0 - 1;
		while (++x < image->width)
		{
			col = trace_ray(scene, image->width, image->height, (t_pixel){x, y});
			mlx_put_pixel(image, x, y, coltouint32_t(col));
		}
	}
	// printf("image drawn");
	// getchar();
}

static int	get_scene_from_input(struct s_scene **scene, int argc, char **argv)
{
	*scene = NULL;
	if (argc != 2)
		printf("Usage: 'miniRT <filename>'\n");
	else
	{
		*scene = parse_file(argv[1]);
		if (*scene == NULL)
			printf("Could not create scene\n");
	}
	if (*scene == NULL)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

static int	window_init(mlx_t **mlx, mlx_image_t **image)
{
	(*mlx) = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (*mlx)
	{
		*image = mlx_new_image(*mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
		if ((*image) && (mlx_image_to_window(*mlx, (*image), 0, 0) >= 0))
			return (EXIT_SUCCESS);
	}
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	struct s_minirt	minirt;	
	int				exit_code;

	minirt.mlx = NULL;
	exit_code = get_scene_from_input(&minirt.scene, argc, argv);
	if (exit_code == EXIT_SUCCESS)
		exit_code = window_init(&minirt.mlx, &minirt.image);
	
	//struct s_shape *shp = minirt.scene->shapes;
	// while (shp != NULL)
	// {
	// 	if (shp->type == e_PLANE) {
	// 		printf("normal @ main %f %f %f\n", ((struct s_plane *)shp)->normal.x, ((struct s_plane *)shp)->normal.y, ((struct s_plane *)shp)->normal.z);
	// 		getchar();
	// 	}
	// }

	if (exit_code == EXIT_SUCCESS)
	{
		mlx_resize_hook(minirt.mlx, (void (*)(int32_t, int32_t, void *))minirt_resize_hook, &minirt);
		mlx_loop_hook(minirt.mlx, (void (*)(void *))minirt_loop_hook, &minirt);
		mlx_key_hook(minirt.mlx, (void (*)(mlx_key_data_t, void *))minirt_key_hook, &minirt);
		mlx_close_hook(minirt.mlx, (void (*)(void *))minirt_close_hook, &minirt);
		mlx_loop(minirt.mlx);
	}
	if (minirt.mlx)
		mlx_terminate(minirt.mlx);
	scene_dtor(&minirt.scene);
	return (exit_code);
}
