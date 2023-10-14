/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:19:38 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 19:36:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static size_t	rt_splitn(char const *s, const char *c)
{
	size_t	nbr;

	nbr = 0;
	while (*s)
	{
		while (ft_strchr(c, *s))
			s++;
		if (*s && !ft_strchr(c, *s))
			nbr++;
		while (*s && !ft_strchr(c, *s))
			s++;
	}
	return (nbr);
}

static size_t	rt_splits(char const *s, const char *c)
{
	size_t	nbr;

	nbr = 0;
	while (*s && !ft_strchr(c, *s))
	{
		s++;
		nbr++;
	}
	return (nbr);
}

static int	rt_splitcpy(char const *src, char *dst, const char *c)
{
	while (*src && !ft_strchr(c, *src))
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
	return (1);
}

static int	rt_splitfree(char **s)
{
	char	**tmp;

	tmp = s;
	while (*s != NULL)
	{
		free (*s);
		s++;
	}
	free (tmp);
	return (1);
}

// Like ft_split but can have multiple different characters as delimiters
char	**rt_split(char const *s, const char *c)
{
	size_t	pos;
	char	**split;
	char	**ret;

	if (s == NULL || c == NULL)
		return (NULL);
	pos = rt_splitn(s, c);
	split = (char **)malloc((pos + 1) * sizeof(char *));
	if (split == NULL || s == NULL)
		return (NULL);
	ret = split;
	while (pos-- > 0)
	{
		while (ft_strchr(c, *s))
			s++;
		*split = (char *)malloc((rt_splits(s, c) + 1) * sizeof(char));
		if (*split == NULL && rt_splitfree(ret))
			return (NULL);
		if (rt_splitcpy(s, *split, c) == 1 && split++)
			while (*s && !ft_strchr(c, *s))
				s++;
	}
	*split = NULL;
	return (ret);
}
