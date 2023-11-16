/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 19:15:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include <stdlib.h>
# include "rt_typedef.h"

// Element base class

struct s_shape
{
	const struct s_shape_vtable	*vtptr;
//	const t_elem_type			type; // Maybe this is not needed
};

struct s_shape_vtable
{
//	void		(*shape_ctor)(struct s_shape *shape, char **args);	// Maybe this is not needed. I assume that constructor has been already called before you could call this
	void		(*shape_dtor)(struct s_shape *shape);
	t_color		(*hit_ray)(struct s_scene *scene, t_ray ray); // placeholder
//	const char	*(*get_element_name)(const struct s_shape *shape);
//	int			(*is_in)(const struct s_shape *shape, t_vector coord);
};

void		shape_ctor(struct s_shape *me, char **args);

void		shape_dtor(struct s_shape *me);

#endif