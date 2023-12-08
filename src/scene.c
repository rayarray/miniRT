/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/08 15:02:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

struct s_scene	*new_scene(void)
{
	struct s_scene	*scene;

	scene = malloc(sizeof(struct s_scene));
	if (scene != NULL)
	{
		scene->ambient = NULL;
		scene->camera = NULL;
		scene->lights = NULL;
		scene->shapes = NULL;
	}
	return (scene);
}

void	scene_dtor(struct s_scene **scene)
{
	if (scene && *scene)
	{
		free((*scene)->ambient);
		free((*scene)->camera);
		light_dtor(&(*scene)->lights);
		shape_list_clear(&(*scene)->shapes);
		free(*scene);
		*scene = NULL;
	}
}
