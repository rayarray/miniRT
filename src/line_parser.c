/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:01:09 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 13:36:20 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_element_type	get_type_and_advance(const char **cptr)
{
	int						i;

	i = -1;
	while (valid_element_ids[++i] != NULL)
	{
		if (ft_strncmp(*cptr, valid_element_ids[i], ft_strlen(valid_element_ids[i])) == 0)
		{
			*cptr += ft_strlen(valid_element_ids[i]);
			break ;
		}
	}
	return ((t_element_type)i);
}

static struct s_element	*element_factory(t_element_type etype)
{
	struct s_element	*e;

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
}

struct s_element		*parse_line(const char *line)
{
	const char				*cptr;
	struct s_element	*elemptr;
	t_element_type		etype;
	char	*args;

	cptr = line;
	while (*cptr != '\0')
	{
		args = rt_split(line, " \t|;");
		skip_whitespace(&cptr);
		etype = get_type_and_advance(&cptr);
		elemptr = element_factory(etype);
		if (elemptr == NULL)
			return (NULL);
		skip_whitespace(&cptr);
		// Continue here. Figure out how to best read input arguments and pass them on
	}
	return (NULL);
}

struct s_element	*parse_lines(const char **lines)
{
	struct s_element	*elemptr;
	int					i;

	i = -1;
	while (lines[++i] != NULL)
	{
		elemptr = parse_line(lines[i]);
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
		printf("%f\n", atof(argv[1]));
	return (0);
}