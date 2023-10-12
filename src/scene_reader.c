/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/12 23:51:10 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

/* static int	read_line(int fd, char **buf)
{
	int		buf_i;
	int		readcount;
	int		totalcount;
	size_t	bufsize;

	buf_i = 0;
	totalcount = 0;
	bufsize = LINE_BUFFER_SIZE;
	*buf = malloc(sizeof(char) * bufsize);
	if (*buf == NULL)
		return (-1);
	while(1)
	{
		readcount = read(fd, &(*buf)[buf_i], 1);
		if (readcount < 0)
		{
			perror("read_line");
			return (-1);
		}
		if (buf_i + 1 == bufsize
				&& ft_realloc((unsigned char **)buf, &bufsize, 2))
			return (-1);
		totalcount += readcount;
		if ((readcount == 0) || (readcount > 0 && (*buf)[buf_i++] == '\n'))
			break;
	}
	(*buf)[buf_i] = '\0';
	return (totalcount);
} */

char	**read_lines(int fd)
{
	char			**lines;
	unsigned int	i;
	size_t			linessize;

	linessize = LINES_BUFFER_SIZE;
	lines = malloc(sizeof(char *) * linessize); //alloc_lines(linessize, linesize);
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