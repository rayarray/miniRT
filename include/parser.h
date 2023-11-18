/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:02:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 15:07:52 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define BASES_BUFFER_SIZE 128
# define REALLOC_FACTOR 2
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "rt_typedef.h"
# include "shape.h"
# include "get_next_line.h"
# include "ambient_lighting.h"
# include "camera.h"
# include "light.h"
# include "shape_cylinder.h"
# include "shape_sphere.h"
# include "shape_plane.h"

typedef enum e_parser_error
{
	e_NO_ERROR,
	e_TOO_MANY_ELEMENTS,
	e_ELEMENT_ARG_ERROR,
	e_ENV_ERROR,
	e_LOGIC_ERROR,
	e_ELEMENT_MISSING_ERROR
}	t_parser_error;

static const char	input_delims[3] = " \t";

static const char	*valid_elem_ids[7] = {"A", "C", "L", "sp", "pl", "cy", NULL};

struct s_elem_base
{
	t_elem_type	type;
	int			(*evaluator)(void *elem, char **args);	// Some type for elem would be nice? Not sure if compiler will accept this
	char		**args;
};

typedef struct s_elem_count
{
	int	elemcount;
	int	cameracount;
	int	ambientcount;
	int	lightcount;
	int	shapecount;
}	t_elem_count;

struct s_scene_base
{
	t_elem_count		count;
	struct s_elem_base	*bases;
};

// Scene_reader.c
struct s_scene	*get_scene(const char *filename);

// Utility functions
char	**free_strarray(char ***array);
int		rt_realloc(unsigned char **buf, size_t *bufsize, int factor);
char	**rt_split(char const *s, const char *c);

// Line_parser.c
//t_elem_type	parse_line(const char *line, struct s_elem_base *elem);
t_parser_error	parse_line_and_create_element(const char *line, struct s_scene *scene);


// Parse the arguments in args and call the constructor
//int		validate_args(e_elem_type type, char **args);		// placeholder
t_parser_error	ambient_lighting_evaluator(struct s_ambient_lighting **a_lt, char **args);
t_parser_error	camera_evaluator(struct s_camera **c, char **args);
t_parser_error	light_evaluator(struct s_light **l, char **args);
t_parser_error	cylinder_evaluator(struct s_cylinder **c, char **args);
t_parser_error	plane_evaluator(struct s_plane **p, char **args);
t_parser_error	sphere_evaluator(struct s_sphere **s, char **args);
t_parser_error	shape_evaluator(struct s_shape **shapes, char **args, t_elem_type type);

// Scene parser
struct s_scene	*create_scene(struct s_scene_base *scenebase);

#endif