/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:00:37 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/02 10:23:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Frees an allocated string array. Returns *array which should be NULL
char	**free_strarray(char ***array)
{
	char	**i;

	if (!array || !*array)
		return (NULL);
	i = *array;
	while (i && *i != NULL)
		free(*(i++));
	free(*array);
	*array = NULL;
	return (*array);
}

// Reallocates an array of data. New size is old size * factor
int	rt_realloc(unsigned char **buf, size_t *bufsize, int factor)
{	// DEPRECATED (it's a good function but probably not needed in this project)
	unsigned char	*newbuf;
	size_t			newsize;

	newsize = factor * (*bufsize);
	newbuf = malloc(sizeof(unsigned char) * newsize);
	if (newbuf == NULL)
	{
		perror("realloc");
		return (1);
	}
	if (ft_memcpy(newbuf, *buf, *bufsize) == NULL)
	{
		printf("realloc: ft_memcpy fail\n");
		return (1);
	}
	free(*buf);
	*buf = newbuf;
	*bufsize = newsize;
	return (0);
}

