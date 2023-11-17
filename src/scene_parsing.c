/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:11:14 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 20:46:51 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "scene.h"
#include "ft_printf.h"

static int	create_elements(struct s_scene *scene, struct s_elem_base *elem,
	int *lights_i, int *shapes_i)
{
	int	err;

	err = 1;
	if (elem->type == e_AMBIENT_LIGHTING)
		err = elem->evaluator(&scene->ambient, elem->args);
	else if (elem->type == e_CAMERA)
		err = elem->evaluator(&scene->camera, elem->args);
	else if (elem->type == e_LIGHT)
	{
		// TODO ALLOCATION!!! (in evaluator)
		err = elem->evaluator(&scene->lights[*lights_i], elem->args);
		if (err == 0)
			++*lights_i;
	}
	else if (elem->type == e_NAE)
	{
		// TODO ALLOCATION!!! (in evaluator)
		err = elem->evaluator(&scene->lights[*shapes_i], elem->args);
		if (err == 0)
			++*shapes_i;
	}
	if (err)
		ft_printf("Error creating element of type %d\n", elem->type);
	return (0);
}

struct s_scene	*create_scene(struct s_scene_base *scenebase)
{	// THIS CODE IS TERRIBLE!!!
	struct s_scene	*scene;
	int				bases_i;
	int				lights_i;
	int				shapes_i;
	int				err;

	bases_i = -1;
	lights_i = 0;
	shapes_i = 0;
	err = scene_ator(&scene, scenebase->count.lightcount, scenebase->count.shapecount);
	while (err == 0 && ++bases_i < scenebase->count.elemcount)
		err = create_element(scene, &scenebase->bases[bases_i], &lights_i, &shapes_i);
	if (err == 0)
		return (scene);
	printf("Error in scene creation\n");
	scene_dtor(&scene);
	return (NULL);
}
