/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:01:39 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "get_next_line_bonus.h"

static void	del_reader(t_reader *reader)
{
	if (reader != NULL)
	{
		free(reader->buf);
		reader->buf = NULL;
		free(reader);
		reader = NULL;
	}
}

static t_reader	*newreader(int fd)
{
	t_reader	*reader;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	reader = malloc(sizeof(t_reader));
	if (reader == NULL)
		return (NULL);
	*(int *)&reader->fd = fd;
	reader->buf = (char *)malloc(BUFFER_SIZE);
	if (reader->buf == NULL)
	{
		del_reader(reader);
		return (NULL);
	}
	reader->head = 0;
	reader->tail = 0;
	return (reader);
}

static t_reader	*get_reader(int fd, t_list **list)
{
	t_reader	*reader;
	t_list		*new_node;

	if (fd < 0)
		return (NULL);
	reader = ft_lstsearch(*list, (void *)&fd, (void *)&reader_match);
	if (reader == NULL)
	{
		reader = newreader(fd);
		if (reader == NULL)
			return (NULL);
		new_node = ft_lstnew(reader);
		if (new_node == NULL)
		{
			del_reader(reader);
			return (NULL);
		}
		new_node->next = *list;
		*list = new_node;
	}
	return (reader);
}

static unsigned int	get_next_char(char *c, t_reader *r)
{
	int	read_count;

	if (r == NULL || c == NULL)
		return (0);
	if (r->head == r->tail)
	{
		r->tail = 0;
		r->head = 0;
		read_count = read(r->fd, r->buf, BUFFER_SIZE);
		if (read_count <= 0)
			return (0);
		r->tail += read_count;
	}
	*c = r->buf[r->head++];
	return (1);
}

/* fd has to be limited arbitrarily because we cannot get exact max value from 
 * system because sysconf is not allowed to be used.
 */
char	*get_next_line(int fd)
{
	static t_list		*readers;
	unsigned int		i;
	char				*line;
	size_t				sz;
	t_reader			*reader;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT32_MAX || LINE_SIZE <= 0
		|| LINE_SIZE > INT32_MAX || fd < 0 || fd > 4096)
		return (NULL);
	sz = LINE_SIZE + 1;
	line = (char *)malloc(sizeof(char) * sz);
	i = 0;
	reader = get_reader(fd, &readers);
	while (sz && line && get_next_char(&line[i], reader) && line[i++] != '\n')
		if (i == sz - 1)
			sz = reallocate_string(&line, sz - 1, (sz - 1) * 2 + 1);
	if (i == 0 || sz <= 0 || line == NULL || reader == NULL)
	{
		ft_lstdelone(&readers, &fd, (int (*)(void *, void *))(*reader_match),
			(void (*)(void *))(*del_reader));
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
