/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 22:40:51 by tsankola         ###   ########.fr       */
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
}	t_elem_type;

static const char	*valid_element_ids[7] = {"A", "C", "L", "sp", "pl", "cy", NULL};

static const struct s_elem *(*element_ators[7])(const char **args);	// dynamic array?

// Element base class //////////////////////////////////////////////////////////

struct s_elem
{
	const struct s_elem_vtable	*vtptr;
	const t_elem_type			type;
	// Insert vtable here with at least: constructor, destructor
};

struct s_elem_vtable
{
	void		(*elem_ctor)(struct s_elem *element, char **args);
	void		(*elem_dtor)(struct s_elem *element);
//	const char	*(*get_element_name)(const struct s_elem *element);
//	int			(*is_in)(const struct s_elem *shape, t_vector coord);
};

void		elem_ctor(struct s_elem *me, char **args);

void		elem_dtor(struct s_elem *me);


////////////////////////////////////////////////////////////////////////////////

struct s_ambient_lighting
{
	struct s_elem			base;
	double					lighting_ratio;
	t_color					color;
};

struct s_camera
{
	struct s_elem			base;
	t_vector				pos;
	t_vector				orientation;
	int						fov;
};

struct s_light
{
	struct s_elem			base;
	t_vector				pos;
	double					brightness;
	t_color					color;
};

struct s_sphere
{
	struct s_elem			base;
	t_vector				pos;
	double					diameter;
	t_color					color;
};

struct s_plane
{
	struct s_elem			base;
	t_vector				point;
	t_vector				normal;
	t_color					color;
};

struct s_cylinder
{
	struct s_elem			base;
	t_vector				pos;
	t_vector				axis;
	double					diameter;
	double					height;
	t_color					color;
};


#endif