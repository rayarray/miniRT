/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:01:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 14:52:33 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ambient_lighting.h"
#include "camera.h"
#include "light.h"
#include "shape_sphere.h"
#include "shape_plane.h"
#include "shape_cylinder.h"
#include "rt_conversions.h"
#include "rt_validations.h"

t_parser_error	ambient_lighting_evaluator(struct s_ambient_lighting **a_lt,
	char **args)
{
	double	light_ratio;
	t_color	color;

	if (args[0] == NULL || args[1] == NULL || args[2] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double(args[1]) || !is_int_triplet_strict(args[2]))
		return (e_ELEMENT_ARG_ERROR);
	*a_lt = malloc(sizeof(struct s_ambient_lighting));
	if (*a_lt == NULL)
		return (e_ENV_ERROR);
	light_ratio = rt_atof(args[1]);
	color = rt_atocol(args[2]);
	if (ambient_lighting_ctor(*a_lt, light_ratio, color))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	camera_evaluator(struct s_camera **c, char **args)
{
	t_vec	loc;
	t_vec	dir;
	int		fov;

	if (args[0] == NULL || args[1] == NULL
		|| args[2] == NULL || args[3] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double_triplet_strict(args[1])
		|| !is_double_triplet_strict(args[2]) || !is_int(args[3]))
		return (e_ELEMENT_ARG_ERROR);
	*c = malloc(sizeof(struct s_camera));
	if (*c == NULL)
		return (e_ENV_ERROR);
	loc = rt_atovec(args[1]);
	dir = rt_atovec(args[2]);
	fov = ft_atoi(args[3]);
	if (camera_ctor(*c, loc, dir, fov))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	light_evaluator(struct s_light **l, char **args)
{
	t_vec			loc;
	double			brightness;
	t_color			color;

	if (args[0] == NULL || args[1] == NULL
		|| args[2] == NULL || args[3] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double_triplet_strict(args[1]) || !is_double(args[2])
		|| !is_int_triplet_strict(args[3]))
		return (e_ELEMENT_ARG_ERROR);
	while (*l != NULL)
		l = &(*l)->next;
	*l = malloc(sizeof(struct s_light));
	if (*l == NULL)
		return (e_ENV_ERROR);
	loc = rt_atovec(args[1]);
	brightness = rt_atof(args[2]);
	color = rt_atocol(args[3]);
	if (light_ctor(*l, loc, brightness, color))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	parse_line_and_create_element(const char *line,
	struct s_scene *scene)
{
	char			**args;
	t_elem_type		type;
	t_parser_error	err;

	type = rt_atoetype(line);
	if (type == e_NAE)
		return (e_NO_ERROR);
	args = rt_split(line, INPUT_DELIMS);
	if (args == NULL)
		err = e_ENV_ERROR;
	else if (type == e_AMBIENT_LIGHTING && scene->ambient == NULL)
		err = ambient_lighting_evaluator(&scene->ambient, args);
	else if (type == e_CAMERA && scene->camera == NULL)
		err = camera_evaluator(&scene->camera, args);
	else if (type == e_LIGHT)
		err = light_evaluator(&scene->lights, args);
	else if (type > e_LIGHT && type < e_NAE)
		err = shape_evaluator(&scene->shapes, args, type);
	else
		err = e_TOO_MANY_ELEMENTS;
	free_strarray(&args);
	if (err != e_NO_ERROR)
		ft_printf("Parse error %d, failed to create element, line:\n%s",
			err, line);
	return (err);
}
