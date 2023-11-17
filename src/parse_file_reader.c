/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_reader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 00:38:52 by tsankola         ###   ########.fr       */
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
		if (err != e_NO_ERROR)
			break ;
		line = get_next_line(fd);
	}
	return (err);
}

static struct s_scene	*read_file(const char *filename)
{
	int				fd;
	struct s_scene	*scene;

	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror(filename);
		return (NULL);
	}
	scene = new_scene();
	if (scene != NULL)
		if (populate_scene(fd, scene) != e_NO_ERROR)
			scene_dtor(&scene);
	if (close(fd) < 0)
		perror(filename);
	return (scene);
}

struct s_scene	*get_scene(const char *filename)
{
	struct s_scene			*scene;

	scene = read_file(filename);
	if (scene == NULL)
		ft_printf("Error when reading file\n");
	ft_printf("scenebase ok\n");
//	if (!scenebase)
//		return (NULL);
//	scene = create_scene(scenebase);
//	ft_printf("create_scene ok\n");
	return (scene);
}
