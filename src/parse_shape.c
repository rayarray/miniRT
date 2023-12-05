/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:30:47 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/05 15:55:46 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_validations.h"
#include "rt_conversions.h"
#include "rt_typedef.h"

t_parser_error	cylinder_evaluator(struct s_cylinder **c, char **args)
{
	t_point3	loc;
	t_vec	axis;
	double	diameter;
	double	height;
	t_color	color;

	if (args[0] == NULL || args[1] == NULL || args[2] == NULL
		|| args[3] == NULL || args[4] == NULL || args[5] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double_triplet_strict(args[1]) || !is_double_triplet_strict(args[2])
		|| !is_double(args[3]) || !is_double(args[4])
		|| !is_int_triplet_strict(args[5]))
		return (e_ELEMENT_ARG_ERROR);
	*c = malloc(sizeof(struct s_cylinder));
	if (*c == NULL)
		return (e_ENV_ERROR);
	loc = rt_atovec(args[1]);
	axis = rt_atovec(args[2]);
	diameter = rt_atof(args[3]);
	height = rt_atof(args[4]);
	color = rt_atocol(args[5]);
	if (cylinder_ctor(*c, loc, axis, (double[2]){diameter, height}, color))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	plane_evaluator(struct s_plane **p, char **args)
{
	t_point3	point;
	t_vec		normal;
	t_color		color;

	if (args[0] == NULL || args[1] == NULL || args[2] == NULL
		|| args[3] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double_triplet_strict(args[1]) || !is_double_triplet_strict(args[2])
		|| !is_int_triplet_strict(args[3]))
		return (e_ELEMENT_ARG_ERROR);
	*p = malloc(sizeof(struct s_cylinder));
	if (*p == NULL)
		return (e_ENV_ERROR);
	point = rt_atovec(args[1]);
	normal = rt_atovec(args[2]);
	color = rt_atocol(args[3]);
	if (plane_ctor(*p, point, normal, color))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	sphere_evaluator(struct s_sphere **s, char **args)
{
	t_vec	loc;
	double	diameter;
	t_color	color;

	if (args[0] == NULL || args[1] == NULL || args[2] == NULL
		|| args[3] == NULL)
		return (e_ELEMENT_ARG_ERROR);
	if (!is_double_triplet_strict(args[1]) || !is_double(args[2])
		|| !is_int_triplet_strict(args[3]))
		return (e_ELEMENT_ARG_ERROR);

	*s = malloc(sizeof(struct s_cylinder));
	if (*s == NULL)
		return (e_ENV_ERROR);
	loc = rt_atovec(args[1]);
	diameter = rt_atof(args[2]);
	color = rt_atocol(args[3]);
	if (sphere_ctor(*s, loc, diameter, color))
		return (e_ELEMENT_ARG_ERROR);
	return (e_NO_ERROR);
}

t_parser_error	shape_evaluator(struct s_shape **shapes, char **args, t_elem_type type)
{
	while (*shapes != NULL)
		shapes = &(*shapes)->next;
	if (type == e_SPHERE)
		return (sphere_evaluator((struct s_sphere **)shapes, args));
	else if (type == e_PLANE)
		return (plane_evaluator((struct s_plane **)shapes, args));
	else if (type == e_CYLINDER)
		return (cylinder_evaluator((struct s_cylinder **)shapes, args));
	return (e_LOGIC_ERROR);
}
