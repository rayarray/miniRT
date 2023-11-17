/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 19:31:22 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include <stdlib.h>
# include "rt_typedef.h"
# include "scene.h"

// Element base class

struct s_scene;
struct s_shape;

struct s_shape_vtable
{
//	void		(*shape_ctor)(struct s_shape *this, char **args);
	void		(*shape_dtor)(struct s_shape *this);
	t_color		(*hit_ray)(struct s_shape *this, struct s_scene *scene, t_ray ray);
//	const char	*(*get_element_name)(const struct s_shape *this);
};

struct s_shape
{
	const struct s_shape_vtable	*vtptr;
	t_elem_type					type;		// Might not be needed but just in case the struct needs to be identified
	t_point						loc;		// Might not be needed but it makes sense for all shapes to have this property
};

void		shape_ctor(struct s_shape *this, t_elem_type type, t_point loc);

void		shape_dtor(struct s_shape *this);

t_color		hit_ray(struct s_shape *this, struct s_scene *scene, t_ray ray);

#endif