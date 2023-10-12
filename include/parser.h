/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:02:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/12 23:51:10 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define LINE_BUFFER_SIZE 128
# define LINES_BUFFER_SIZE 128
# define REALLOC_FACTOR 2
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
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

struct s_element
{
	t_element_type	type;
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

// Scene_reader.c
struct s_element	*get_scene(const char *filename);

// Utility functions
char	**free_strarray(char ***array);
int		rt_realloc(unsigned char **buf, size_t *bufsize, int factor);
char	**alloc_lines(size_t arraysize, size_t linesize);
double	rt_atof(const char *a);
int		skip_whitespace(const char **cptr);

// Line_parser.c
struct s_element	*parse_lines(const char **lines);

#endif