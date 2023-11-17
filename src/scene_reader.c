/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/17 19:55:45 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "scene.h"
#include "camera.h"
#include "libft.h"

static size_t	realloc_bases(struct s_elem_base **bases, size_t *old_size)
{
	int	err_chk;
	
	*old_size *= sizeof((*bases)[0]);
	err_chk = rt_realloc((unsigned char **)bases, old_size, REALLOC_FACTOR);
	*old_size /= sizeof((*bases)[0]);
	return (err_chk);
}

static t_elem_count	get_bases(int fd, struct s_elem_base **bases, size_t bufsize)
{
	int				err;
	unsigned int	i;
	char			*line;
	t_elem_count	count;

	i = 0;
	line = get_next_line(fd);
	count = (t_elem_count){0, 0, 0, 0, 0};
	while (line != NULL)
	{
		err = parse_line_and_increment_counter(line, &(*bases)[i], &count);
		free(line);
		if (err == 0 && ++i == bufsize - 1)			// bad bit of code here with the '++i'
			err = realloc_bases(bases, &bufsize);
		if (err > 0)
		{
			while (i > 0)
				free_strarray(&bases[--i]->args);	// TODO sanity check for index logic
			return ((t_elem_count){-1,-1,-1,-1,-1});
		}
		line = get_next_line(fd);
	}
	return (count);
}

static struct s_scene_base	*read_lines(int fd)
{
	t_elem_count		count;
	struct s_elem_base	*elem_bases;
	struct s_scene_base	*scene_base;

	scene_base = NULL;
	elem_bases = malloc(sizeof(struct s_elem_base) * BASES_BUFFER_SIZE);
	if (elem_bases == NULL)
		return (NULL);
	count = get_bases(fd, &elem_bases, BASES_BUFFER_SIZE);
	if (count.ambientcount != 1 || count.cameracount != 1
		|| count.lightcount < 0 || count.shapecount < 0
		|| (count.ambientcount + count.cameracount 
			+ count.lightcount + count.shapecount) != count.elemcount)
		free(elem_bases);	// TODO print error message here
	else
	{
		scene_base = malloc(sizeof(struct s_scene_base));
		if (scene_base == NULL)
			free(elem_bases);
		else
		{
			scene_base->bases = elem_bases;
			scene_base->count = count;
		}
	}
	return (scene_base);
}

static struct s_scene_base	*get_elem_bases(const char *filename)
{
	int					fd;
	struct s_scene_base	*scenebase;

	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror(filename);
		return (NULL);
	}
	scenebase = read_lines(fd);
	if (close(fd) < 0)
		perror(filename);
	return (scenebase);
}

struct s_scene	*get_scene(const char *filename)
{
	struct s_scene_base		*scenebase;
	struct s_scene			*scene;

	scenebase = get_elem_bases(filename);
	ft_printf("scenebase ok\n");
	if (!scenebase)
		return (NULL);
	scene = create_scene(scenebase);
	ft_printf("create_scene ok\n");
	return (scene);
}
