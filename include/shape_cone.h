/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:07 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 16:27:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_CONE_H
# define SHAPE_CONE_H
# include "shape.h"
# include "rt_typedef.h"
# include "rt_math.h"

typedef enum e_cone_ray_position
{
	e_INSIDE_CONE,
	e_OVER_CONE,
	e_BESIDE_CONE,
	e_UNDER_CONE
}	t_cone_ray_pos;

typedef enum e_cone_dimension_index
{
	e_CONE_DIAMETER,
	e_CONE_HEIGHT
}	t_cone_dimension_index;

typedef enum e_cone_orientation_index
{
	e_CONE_LOCATION,
	e_CONE_AXIS
}	t_cone_orientation_index;

struct s_cone
{
	struct s_shape	base;
	t_vec			axis;
	t_vec			vertex;
	double			diameter;
	double			height;
	double			angle;
};

int				cone_ctor(struct s_cone *c, t_vec orientation[2],
					double dimensions[2], t_color color);
void			cone_dtor(struct s_cone *c);
double			cone_intersect_distance(struct s_cone *c, t_ray ray);
t_color			cone_intersect_color(struct s_cone *c,
					struct s_scene *scene, t_ray ray, int bounces);

// shape_cone_utils.c
double			test_results(struct s_cone *c, t_ray ray,
					int results, double isects[2]);
t_cone_ray_pos	get_ray_position(struct s_cone *c, t_ray ray);
double			cone_base_intersection(struct s_cone *c, t_ray ray);
double			check_hit_location(struct s_cone *c, t_ray ray,
					double distance);

#endif