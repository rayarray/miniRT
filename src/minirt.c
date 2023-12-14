/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:12 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/14 15:33:21 by rleskine         ###   ########.fr       */
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
#include "render.h"

void	tests()
{
	double test = vecLength(vecInit(-0.901, 0.576, 1));
	printf("test: %f\n", test);
	t_vec dist = vecCross(vecInit(-1,0,1), vecInit(1,0,2));
	vecPrint("dist", dist, 1);
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
	struct s_minirt	data;	
	int				exit_code;

	tests();
	data.mlx = NULL;
	exit_code = get_scene_from_input(&data.scene, argc, argv);
	if (exit_code == EXIT_SUCCESS)
		exit_code = window_init(&data.mlx, &data.image);
	if (exit_code == EXIT_SUCCESS)
	{
		mlx_resize_hook(data.mlx,
			(void (*)(int32_t, int32_t, void *))minirt_resize_hook, &data);
		mlx_loop_hook(data.mlx, (void (*)(void *))minirt_loop_hook, &data);
		mlx_key_hook(data.mlx,
			(void (*)(mlx_key_data_t, void *))minirt_key_hook, &data);
		mlx_close_hook(data.mlx, (void (*)(void *))minirt_close_hook, &data);
		mlx_loop(data.mlx);
	}
	if (data.mlx)
		mlx_terminate(data.mlx);
	scene_dtor(&data.scene);
	return (exit_code);
}
