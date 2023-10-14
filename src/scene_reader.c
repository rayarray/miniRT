/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 20:47:19 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	realloc_bases(struct s_element_base **bases, size_t *old_size)
{
	int	err_chk;
	
	*old_size *= sizeof((*bases)[0]);
	err_chk = rt_realloc((unsigned char **)bases, old_size, REALLOC_FACTOR);
	*old_size /= sizeof((*bases)[0]);
	return (err_chk);
}

static int	read_line(int fd, struct s_element_base **bases, size_t bufsize)
{
	int				err;
	unsigned int	i;
	char			*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		err = parse_line(line, &(*bases)[i]);
		free(line);
		if (err == 0 && ++i == bufsize - 1)
			err = realloc_bases(bases, &bufsize);
		if (err > 0)
		{
			while (i > 0)
				free_strarray(&bases[--i]->args);	// TODO sanity check for index logic
			return (-1);
		}
		line = get_next_line(fd);
	}
	return ((int)i);
}

static int	read_lines(int fd, struct s_element_base **elem_bases)
{
	int		i;
	size_t	bufsize;

	bufsize = BASES_BUFFER_SIZE;
	*elem_bases = malloc(sizeof(struct s_element_base) * bufsize);
	if (*elem_bases == NULL)
		return (-1);
	i = read_line(fd, elem_bases, bufsize);
	if (i < 0)
	{
		free(*elem_bases);
		*elem_bases = NULL;
	}
	return (i);
}

static int	get_elem_bases(const char *filename, struct s_element_base **bases)
{
	int		fd;
	int		linecount;

	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	linecount = read_lines(fd, bases);
	if (close(fd) < 0)
		perror(filename);
	return (linecount);
}

struct s_element_base	*get_scene(const char *filename)
{
	struct s_element_base	*bases;
	int						linecount;
	
	linecount = get_elem_bases(filename, &bases);
	if (linecount < 0)
		return (NULL);
	// TODO create elements here?
	return (bases);
}