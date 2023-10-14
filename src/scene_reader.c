/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/13 18:05:57 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

char	**read_lines(int fd)
{
	char			**lines;
	unsigned int	i;
	size_t			linessize;

	linessize = LINES_BUFFER_SIZE;
	lines = malloc(sizeof(char *) * linessize);
	if (lines == NULL)
		return (NULL);
	i = 0;
	lines[i] = get_next_line(fd);
	while (lines[i] != NULL)
	{
		if (++i == linessize)
		{
			linessize *= sizeof(lines[0]);
			if (rt_realloc((unsigned char **)&lines, &linessize, REALLOC_FACTOR))
				return (free_strarray(&lines));
			linessize /= sizeof(lines[0]);
		}
		lines[i] = get_next_line(fd);
	}
	return (lines);
}
static char	**get_lines(const char *filename)
{
	char	**lines;
	int		fd;

	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror(filename);
		return (NULL);
	}
	lines = read_lines(fd);
	if (close(fd) < 0)
		perror(filename);
	return (lines);
}

struct s_element	*get_scene(const char *filename)
{
	char	**lines;
	
	lines = get_lines(filename);
	return (NULL);
}