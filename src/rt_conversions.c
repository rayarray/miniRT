/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:56:43 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 20:32:05 by tsankola         ###   ########.fr       */
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

t_element_type	rt_atoetype(const char *a)
{
	int	i;
	int	len;

	i = -1;
	skip_whitespace(&a);
	while (valid_element_ids[++i] != NULL)
	{
		len = ft_strlen(valid_element_ids[i]);
		if (ft_strncmp(a, valid_element_ids[i], len) == 0
			&& ft_strchr(" \t", *(a + len)))
			break ;
	}
	return ((t_element_type)i);
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

t_vector	rt_atovec(const char *a)
{	// TODO check against malformed input
	t_vector	vec;

	vec.x = rt_atof(a);
	a = ft_strchr(a, ',');
	vec.y = rt_atof(++a);
	a = ft_strchr(a, ',');
	vec.z = rt_atof(++a);
	return (vec);
}

t_color	rt_atocol(const char *a)
{	// TODO check against malformed input
	t_color	col;

	col.red = (unsigned char)atoi(a);
	a = ft_strchr(a, ',');
	col.green = (unsigned char)atoi(++a);
	a = ft_strchr(a, ',');
	col.blue = (unsigned char)atoi(++a);
	return (col);
}

int	rt_atofov(const char *a)
{	// TODO check against malformed input
	int	fov;

	fov = atoi(a);
	if (fov > 180)
		fov = 180;
	if (fov < 0)
		fov = 0;
	return (fov);
}

t_vector	rt_atonorm(const char *a)
{	// TODO check against malformed input
	t_vector	norm;

	norm = rt_atovec(a);
	if (norm.x > 1.0)
		norm.x = 1.0;
	if (norm.y > 1.0)
		norm.y = 1.0;
	if (norm.y > 1.0)
		norm.y = 1.0;
	if (norm.x < -1.0)
		norm.x = -1.0;
	if (norm.y < -1.0)
		norm.y = -1.0;
	if (norm.y < -1.0)
		norm.y = -1.0;
	return (norm);
}

double	rt_atolight(const char *a)
{	// TODO check against malformed input
	double	light;

	light = rt_atof(a);
	if (light > 1.0)
		light = 1.0;
	if (light < -1.0)
		light = -1.0;
	return (light);
}
