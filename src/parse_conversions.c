/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:56:43 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/19 17:57:57 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_conversions.h"

static int	skip_whitespace(const char **cptr)
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

t_elem_type	rt_atoetype(const char *a)
{
	int	i;
	int	len;

	i = -1;
	skip_whitespace(&a);
	while (valid_elem_ids[++i] != NULL)
	{
		len = ft_strlen(valid_elem_ids[i]);
		if (ft_strncmp(a, valid_elem_ids[i], len) == 0
			&& ft_strchr(" \t", *(a + len)))
			break ;
	}
	return ((t_elem_type)i);
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
	sign -= ((*c == '-') * 2);
	c += (*c == '+' || *c == '-');
	while (ft_isdigit(*c))
		f = f * 10 + sign * (*c++ - '0');
	if (*c++ != '.')
		return (f);
	while (ft_isdigit(*c))
	{
		f = f + sign * ((double)(*c++ - '0')) / fractions;
		fractions *= 10;
	}
	return (f);
}

t_vec	rt_atovec(const char *a)
{
	t_vec	vec;

	vec.x = rt_atof(a);
	a = ft_strchr(a, ',');
	vec.y = rt_atof(++a);
	a = ft_strchr(a, ',');
	vec.z = rt_atof(++a);
	return (vec);
}

t_color	rt_atocol(const char *a)
{
	t_color	col;

	col.r = (unsigned char)atoi(a);
	a = ft_strchr(a, ',');
	col.g = (unsigned char)atoi(++a);
	a = ft_strchr(a, ',');
	col.b = (unsigned char)atoi(++a);
	col.a = 0xFF;
	return (col);
}
