/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 23:57:28 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include <stdlib.h>
# include "rt_typedef.h"
# include "scene.h"

// Shape base class. Should not be instantiated

struct s_scene;
struct s_shape;

struct s_shape_vtable
{
	void		(*shape_dtor)(struct s_shape *this);
	bool		(*intersect)(struct s_shape *this, t_ray ray);
	t_point3	(*intersect_location)(struct s_shape *this, t_ray ray);
	t_color		(*get_color)(struct s_shape *this, struct s_scene *scene, t_ray ray);
};

struct s_shape
{
	const struct s_shape_vtable	*vtptr;
	struct s_shape				*next;		// For linked list
	t_elem_type					type;		// Might not be needed but just in case the struct needs to be identified
	t_point3					loc;		// Might not be needed but it makes sense for all shapes to have this property
	// color?
};

void		shape_ctor(struct s_shape *this, t_elem_type type, t_point3 loc);

void		_shape_base_dtor(struct s_shape *this);

void		shape_dtor(struct s_shape *this);

t_color		hit_ray(struct s_shape *this, struct s_scene *scene, t_ray ray);

void		shape_list_clear(struct s_shape **shape);

#endif