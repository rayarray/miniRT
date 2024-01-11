/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:15 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CYLINDER_H
# define SHAPE_CYLINDER_H
# include "rt_typedef_bonus.h"
# include "shape_bonus.h"

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
	double	dist;
	int		surf;
}	t_surface_hits;

typedef struct s_cylinder_products
{
	t_vec	rc;
	t_vec	nv;
	t_vec	dv;
	t_vec	ov;
	double	ln;
	double	d;
	double	t;
	double	s;
}	t_cylinder_products;

int				cylinder_ctor(struct s_cylinder *this, t_vec orientation[2],
					double dimensions[2], t_color color);

void			cylinder_dtor(struct s_cylinder *this);

double			cylinder_intersect_distance(struct s_cylinder *this, t_ray ray);

t_color			cylinder_intersect_color(struct s_cylinder *this,
					struct s_scene *scene, t_ray ray, int bounces);

int				infinite_cylinder_intersect(struct s_cylinder *this, t_ray ray,
					t_surface_hits *hit, t_cylinder_products var);

int				cylinder_clip_cap2(t_surface_hits *hit, double dc, double dw);

double			cylinder_clip_cap(struct s_cylinder *this, t_ray ray,
					t_surface_hits *hit, t_plane_eq pln);

t_surface_hits	cylinder_intersect_hits(struct s_cylinder *this, t_ray ray);

int				cylinder_within_shape(struct s_cylinder *this, t_point3 loc);

#endif