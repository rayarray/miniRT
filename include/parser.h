/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:02:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/18 18:07:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define BASES_BUFFER_SIZE 128
# define REALLOC_FACTOR 2
# define INPUT_DELIMS " \t\n"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "rt_typedef.h"
# include "get_next_line.h"
# include "ambient_lighting.h"
# include "camera.h"
# include "light.h"
# include "shape.h"
# include "shape_cylinder.h"
# include "shape_sphere.h"
# include "shape_plane.h"
# include "shape_cone.h"

typedef enum e_parser_error
{
	e_NO_ERROR,
	e_TOO_MANY_ELEMENTS,
	e_ELEMENT_ARG_ERROR,
	e_SYS_ERROR,
	e_LOGIC_ERROR,
	e_ELEMENT_MISSING_ERROR
}	t_parser_error;

struct s_elem_base
{
	t_elem_type	type;
	int			(*evaluator)(void *elem, char **args);
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

// parse_file_reader.c
struct s_scene	*parse_file(const char *filename);

// Utility functions
char			**free_strarray(char ***array);
char			**rt_split(char const *s, const char *c);

// parse_scene.c
t_parser_error	parse_line_and_create_element(const char *line,
					struct s_scene *scene);

// Parse the arguments in args and call the constructor
t_parser_error	ambient_lighting_evaluator(struct s_ambient_lighting **a_lt,
					char **args);
t_parser_error	camera_evaluator(struct s_camera **c, char **args);
t_parser_error	light_evaluator(struct s_light **l, char **args);
t_parser_error	cylinder_evaluator(struct s_cylinder **c, char **args);
t_parser_error	plane_evaluator(struct s_plane **p, char **args);
t_parser_error	sphere_evaluator(struct s_sphere **s, char **args);
t_parser_error	shape_evaluator(struct s_shape **shapes, char **args,
					t_elem_type type);

#endif