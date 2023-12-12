/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_reader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/02 10:22:49 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "scene.h"
#include "camera.h"
#include "libft.h"

static t_parser_error	populate_scene(int fd, struct s_scene *scene)
{
	t_parser_error	err;
	char			*line;

	err = e_ENV_ERROR;
	line = get_next_line(fd);
	while (line != NULL)
	{
		err = parse_line_and_create_element(line, scene);
		free(line);
		if (err != e_NO_ERROR && err != e_ELEMENT_ARG_ERROR)
			break ;
		line = get_next_line(fd);
	}
	if (scene->ambient == NULL || scene->camera == NULL)
	{
		ft_printf("Vital element missing\n");
		return (e_ELEMENT_MISSING_ERROR);
	}
	// TODO Should add check for multiple lights for mandatory part here
	return (err);
}

struct s_scene	*parse_file(const char *filename)
{
	int				fd;
	struct s_scene	*scene;

	scene = NULL;
	fd = open(filename, O_DIRECTORY);
	if (fd < 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			perror(filename);
			return (NULL);
		}
		scene = new_scene();
		if (scene != NULL)
			if (populate_scene(fd, scene) != e_NO_ERROR)
				scene_dtor(&scene);
	}
	else
		ft_printf("%s is a directory.\n", filename);
	if (close(fd) < 0)
		perror(filename);
	return (scene);
}
