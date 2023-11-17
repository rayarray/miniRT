/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:30:47 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 21:09:49 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_validations.h"
#include "rt_conversions.h"

int	ambient_lighting_evaluator(struct s_ambient_lighting *a_lt, char **args)
{
	double	light_ratio;
	t_color	color;
	// TODO check arg_count
	if (!is_double(args[0]) || !is_int_triplet_strict(args[1]))
		return (1);
	light_ratio = rt_atof(args[0]);
	color = rt_atocol(args[1]);
	return (ambient_lighting_ctor(a_lt, light_ratio, color));
}

int	camera_evaluator(struct s_camera *c, char **args)
{
	t_vec	loc;
	t_vec	dir;
	int		fov;
	// TODO check arg_count
	if (!is_double_triplet_strict(args[0])
		|| !is_double_triplet_strict(args[1]) || !is_int(args[2]))
		return (1);
	loc = rt_atovec(args[0]);
	dir = rt_atovec(args[1]);
	fov = ft_atoi(args[3]);
	return (camera_ctor(c, loc, dir, fov));
}

int	light_evaluator(struct s_light **l, const char **args)
{
	t_vec			pos;
	double			brightness;
	t_color			color;
	// TODO check arg_count
	if (!is_double_triplet_strict(args[0]) || !is_double(args[1])
		|| !is_int_triplet_strict(args[2]))
		return (1);
	*l = malloc(sizeof(struct s_light));
	if (*l == NULL)
		return (2);
	pos = rt_atovec(args[0]);
	brightness = rt_atof(args[1]);
	color = rt_atocol(args[2]);
	return (light_ctor(*l, pos, brightness, color));
}

int		cylinder_evaluator(struct s_cylinder **c, char **args)
{
	t_point	loc;
	t_vec	axis;
	double	diameter;
	double	height;
	t_color	color;

	if (!is_double_triplet_strict(args[0]) || !is_double_triplet_strict(args[1])
		|| !is_double(args[2]) || !is_double(args[3])
		|| !is_int_triplet_strict(args[4]))
		return (1);
	*c = malloc(sizeof(struct s_cylinder));
	if (c == NULL)
		return (2);
	loc = rt_atovec(args[0]);
	axis = rt_atovec(args[1]);
	diameter = rt_atof(args[2]);
	height = rt_atof(args[3]);
	color = rt_atocol(args[4]);
	return (cylinder_ctor(*c, loc, axis, (double[2]){diameter, height}, color));
}

int		plane_evaluator(struct s_plane **plane, char **args)
{
	(void)plane;
	(void)args;
	return 0;
}

int		sphere_evaluator(struct s_sphere **sphere, char **args)
{
	(void)sphere;
	(void)args;
	return 0;
}