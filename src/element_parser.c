/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:30:47 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 17:46:16 by tsankola         ###   ########.fr       */
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

int	light_evaluator(struct s_light *l, const char **args)
{
	t_vec			pos;
	double			brightness;
	t_color			color;
	// TODO check arg_count
	if (!is_double_triplet_strict(args[0]) || !is_double(args[1])
		|| !is_int_triplet_strict(args[2]))
		return (1);
	pos = rt_atovec(args[0]);
	brightness = rt_atof(args[1]);
	color = rt_atocol(args[2]);
	return (light_ctor(l, pos, brightness, color));
}
