/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:00:37 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/12 23:58:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	skip_whitespace(const char **cptr)
{
	int	n;

	n = 0;
	while(1 <= **cptr && **cptr <= ' ')
	{
		(*cptr)++;
		n++;
	}
	return (n);
}

double	rt_atof(const char *a)
{
	const char			*c;
	double				f;
	int					sign;
	unsigned long int	fractions;

	fractions = 10;
	c = a;
	f = 0;
	sign = 1;
	skip_whitespace(&c);
	sign -= ((*c == '-') * -2);
	c += (*c == '+' || *c == '-');
	while (ft_isdigit(*c))
		f = f * 10 + sign * (*c++ - '0');
	if (*c++ != '.')
		return (f);
	while (ft_isdigit(*c))
	{
		f = f + sign * ((double)(*c - '0')) / fractions;
		fractions *= 10;
	}
	return (f);
}

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

int	rt_realloc(unsigned char **buf, size_t *bufsize, int factor)
{
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

char	**alloc_lines(size_t arraysize, size_t linesize)
{
	char	**lines;
	int		i;

	lines = malloc(sizeof(char *) * arraysize);
	if (lines == NULL)
	{
		perror("alloc_lines");
		return (NULL);
	}
	i = -1;
	while ((size_t)(++i) < arraysize)
	{
		lines[i] = malloc(sizeof(char) * linesize);
		if (lines[i] == NULL)
		{
			perror("alloc_lines");
			return (free_strarray(&lines));
		}
	}
	return (lines);
}
