/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:15 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/03 11:13:30 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CYLINDER_H
# define SHAPE_CYLINDER_H
# include "rt_typedef.h"
# include "shape.h"

# define CYL_SIDE	0
# define CYL_BOT	1
# define CYL_TOP	2

typedef enum e_cylinder_dimension_index
{
	e_DIAMETER,
	e_HEIGHT
}	t_cylinder_dimension_index;

typedef enum e_cylinder_orientation_index
{
	e_LOCATION,
	e_AXIS
}	t_cylinder_orientation_index;

struct s_cylinder
{
	struct s_shape	base;
	t_vec			axis;
	t_point3		center;
	double			radius;
	double			rad2;
	double			diameter;
	double			dia2;
	double			height;
	t_plane_eq		top;
	t_plane_eq		bot;
	int				debug;
};

typedef struct s_surface_hits
{
	int		surfin;
	double	in;
	int		surfout;
	double	out;
	int		pass;
}	t_surface_hits;

int		cylinder_ctor(struct s_cylinder *this, t_vec orientation[2],
			double dimensions[2], t_color color);

void	cylinder_dtor(struct s_cylinder *this);

double	cylinder_intersect_distance(struct s_cylinder *this, t_ray ray);

t_color	cylinder_intersect_color(struct s_cylinder *this,
			struct s_scene *scene, t_ray ray, int bounces);

#endif