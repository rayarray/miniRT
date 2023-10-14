/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 20:37:59 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# include <stdlib.h>
# include "rt_typedef.h"

typedef enum	e_element_type
{
	e_AMBIENT_LIGHTING = 0,
	e_CAMERA = 1,
	e_LIGHT = 2,
	e_SPHERE = 3,
	e_PLANE = 4,
	e_CYLINDER = 5,
	e_NAE = 6
}	t_element_type;

static const char	*valid_element_ids[7] = {"A", "C", "L", "sp", "pl", "cy", NULL};

static const struct s_element *(*element_ators[7])(const char **args);	// dynamic array?

struct s_element
{
	t_element_type	type;
	// Insert vtable here with at least: constructor, destructor
};


struct s_ambient_lighting
{
	struct s_element		base;
	double					lighting_ratio;
	t_color					color;
};

struct s_camera
{
	struct s_element		base;
	t_vector				pos;
	t_vector				orientation;
	int						fov;
};

struct s_light
{
	struct s_element		base;
	t_vector				pos;
	double					brightness;
	t_color					color;
};

struct s_sphere
{
	struct s_element		base;
	t_vector				pos;
	double					diameter;
	t_color					color;
};

struct s_plane
{
	struct s_element		base;
	t_vector				point;
	t_vector				normal;
	t_color					color;
};

struct s_cylinder
{
	struct s_element		base;
	t_vector				pos;
	t_vector				axis;
	double					diameter;
	double					height;
	t_color					color;
};


#endif