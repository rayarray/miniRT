/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:01:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 20:37:47 by tsankola         ###   ########.fr       */
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

/* static struct s_shape	*element_factory(t_elem_type etype)
{
	struct s_shape	*e;

	e = NULL;
	if (etype == e_AMBIENT_LIGHTING)
		e = malloc(sizeof(struct s_ambient_lighting));
	else if (etype == e_CAMERA)
		e = malloc(sizeof(struct s_camera));
	else if (etype == e_LIGHT)
		e = malloc(sizeof(struct s_light));
	else if (etype == e_SPHERE)
		e = malloc(sizeof(struct s_sphere));
	else if (etype == e_PLANE)
		e = malloc(sizeof(struct s_plane));
	else if (etype == e_CYLINDER)
		e = malloc(sizeof(struct s_cylinder));
	if (e != NULL)
		e->type = etype;
	return (e);
} */

static void	assign_ctor(struct s_elem_base *elem)
{
	if (elem->type == e_AMBIENT_LIGHTING)
		elem->evaluator = (int (*)(void *, char **))ambient_lighting_evaluator;
	else if (elem->type == e_CAMERA)
		elem->evaluator = (int (*)(void *, char **))camera_evaluator;
	else if (elem->type == e_LIGHT)
		elem->evaluator = (int (*)(void *, char **))light_evaluator;
	else if (elem->type == e_SPHERE)
		elem->evaluator = (int (*)(void *, char **))sphere_evaluator;
	else if (elem->type == e_PLANE)
		elem->evaluator = (int (*)(void *, char **))plane_evaluator;
	else if (elem->type == e_CYLINDER)
		elem->evaluator = (int (*)(void *, char **))cylinder_evaluator;
	else
		elem->evaluator = NULL;
}

t_elem_type	parse_line_and_increment_counter(const char *line,
	struct s_elem_base *elem, t_elem_count *counter)
{	// Arguments could be validated here
	elem->type = rt_atoetype(line);
	if (elem->type == e_NAE)
		return (-1);
	elem->args = rt_split(line, delims);
	if (elem->args == NULL)
		return (1);
	assign_ctor(elem);
	if (elem->type == e_CAMERA)
		counter->cameracount++;
	else if (elem->type == e_AMBIENT_LIGHTING)
		counter->ambientcount++;
	else if (elem->type == e_LIGHT)
		counter->lightcount++;
	else if (elem->type != e_NAE)
		counter->shapecount++;
	counter->elemcount++;
	return (0);
}
