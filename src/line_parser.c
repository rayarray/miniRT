/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:01:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 21:28:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* static struct s_elem	*element_factory(t_elem_type etype)
{
	struct s_elem	*e;

	e = NULL;
	if (etype == e_AMBIENT_LIGHTING)
		e = malloc(sizeof(struct s_ambient_lighting));
	else if (etype == e_CAMERA)
		e = malloc(sizeof(struct s_camera));
	else if (etype == e_LIGHT)
		e = malloc(sizeof(struct s_light));
	else if (etype == e_SPHERE)
		e = malloc(sizeof(struct s_sphere));
	else if (etype == e_PLANE)
		e = malloc(sizeof(struct s_plane));
	else if (etype == e_CYLINDER)
		e = malloc(sizeof(struct s_cylinder));
	if (e != NULL)
		e->type = etype;
	return (e);
} */

int	parse_line(const char *line, struct s_elem_base *elem)
{
	char	**args;

	elem->type = rt_atoetype(line);
	elem->args = NULL;
	if (elem->type == e_NAE)
		return (-1);
	args = rt_split(line, delims);
	if (args == NULL)
		return (1);
	elem->args = args;
	return (0);
}


int main(int argc, char *argv[])
{
	struct s_elem_base	*bases;
	if (argc == 2)
	{
		bases = get_scene(argv[1]);
	}
	return (0);
}