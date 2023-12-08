/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 16:09:10 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include <stdlib.h>
# include "rt_typedef.h"
# include "scene.h"

// Shape base class. Should not be instantiated

struct	s_scene;
struct	s_shape;

// Virtual table, containing the "methods" of this class
struct s_shape_vtable
{
	void	(*shape_dtor)(struct s_shape *);
	double	(*intersect_distance)(struct s_shape *, t_ray);
	t_color	(*intersect_color)(struct s_shape *, struct s_scene *, t_ray);
};

/*
	vtptr	points to the vtable of the class
	next	is there to support linked lists of shapes. I would like it if the
			shapes were in some actual data structure, but this linking should
			do for this project
	type	contains the type of the object. Convenient but not necessary
	loc		location of the shape
	color	color of the shape
*/
struct s_shape
{
	const struct s_shape_vtable	*vtptr;
	struct s_shape				*next;
	t_elem_type					type;
	t_vec						loc;
	t_color						col;
};

void	shape_ctor(struct s_shape *this, t_elem_type type, t_vec loc,
			t_color col);

void	_shape_base_dtor(struct s_shape *this);

void	shape_dtor(struct s_shape *this);

double	intersect_distance(struct s_shape *this, t_ray ray);

t_color	intersect_color(struct s_shape *this, struct s_scene *scene, t_ray ray);

void	shape_list_clear(struct s_shape **shape);

#endif