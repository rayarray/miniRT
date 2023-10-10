/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:45:14 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/10 20:37:21 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H
# include <stdlib.h>
# include "libft.h"

typedef enum e_color_index
{
	RED = 0,
	GREEN = 1,
	BLUE = 2
}	t_color_i;

typedef enum e_coordinate_index
{
	X = 0,
	Y = 1,
	Z = 2
}	t_coord_i;


// Trying to implement polymorphism here: Each object type should be able to be
// cast as t_shape. They share members: identifier, coordinates, color.
// t_shape could encompass t_light as well, but it does not have a form and it
// seems like it should be a special case, so...
// There could be another super class called "placeable" which would share
// coordinates.

typedef struct s_shape
{
	void (*print)(int x, struct s_shape);
}	t_shape;

/* typedef struct s_shape
{
	const char *identifier;
	double	coordinates[3];
	int		color[3];
}	t_shape;
 */

typedef struct s_ambient_lighting
{
	const char *identifier;
	int		color[3];
	double	lighting_ratio;
}	t_ambient_lighting;

typedef struct s_camera
{
	const char *identifer;
	double	coordinates[3];
	double	orientation_vector[3];
	int		fov;
}	t_camera;

typedef struct s_light
{
	const char *identifier;
	double	coordinates[3];
	int		color[3];
	double	brightness;
}	t_light;

typedef struct s_sphere
{
	const char *identifier;
	double	coordinates[3];
	int		color[3];
	double	diameter;
}	t_sphere;

typedef struct s_plane
{
	const char *identifier;
	double	coordinates[3];
	int		color[3];
	double	normal_vector[3];
}	t_plane;

typedef struct s_cylinder
{
	const char *identifier;
	double	coordinates[3];
	int		color[3];
	double	axis[3];
	double	diameter;
	double	height;
}	t_cylinder;

// Constructors for each type of element. Returns a pointer to the created
// object. If malloc fails, return NULL.
t_ambient_lighting	*new_ambient_lighting(const char *identifier);
t_camera			*new_camera(const char *identifier);
t_light				*new_light(const char *identifier);
t_sphere			*new_sphere(const char *identifier);
t_plane				*new_plane(const char *identifier);
t_cylinder			*new_cylinder(const char *identifier);

// Destructors for each type of element. Returns a pointer to the created
// object. If malloc fails, return NULL.
void	del_ambient_lighting(t_ambient_lighting **al);
void	del_camera(t_camera **al);
void	del_light(t_light **al);
void	del_sphere(t_sphere **al);
void	del_plane(t_plane **al);
void	del_cylinder(t_cylinder **al);

#endif