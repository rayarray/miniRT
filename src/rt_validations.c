/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:02:19 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/02 10:27:18 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_validations.h"

// Value form checking

// Checks if the string pointed at by s represents a double value and returns
// its length
int	is_double(const char *s)
{
	int	digit_found;
	int	len;

	digit_found = 0;
	len = 0;
	if (s[len] == '+' || s[len] == '-')
		len++;
	while (ft_isdigit(s[len]))
	{
		digit_found = 1;
		len++;
	}
	if (s[len] == '.')
	{
		len++;
		if (!ft_isdigit(s[len]))
			return (0);
		digit_found = 1;
		while (ft_isdigit(s[len]))
			len++;
	}
	if (!digit_found)
		return (0);
	return (len);
}

int	is_int(const char *s)
{
	int	digit_found;
	int	len;

	digit_found = 0;
	len = 0;
	if (s[len] == '+' || s[len] == '-')
		len++;
	while (ft_isdigit(s[len]))
	{
		digit_found = 1;
		len++;
	}
	if (!digit_found)
		return (0);
	return (len);
}

int	is_double_triplet_strict(const char *s)
{
	int	total_length;
	int	length;
	int	values_found;
	int	passes;

	total_length = 0;
	values_found = 0;
	passes = 0;
	while (1)
	{
		passes++;
		length = is_double(&s[total_length]);
		if (length > 0)
			values_found++;
		total_length += length;
		if (passes == 3 || s[total_length++] != TRIPLET_DELIM)
			break ;
	}
	if (values_found == 3 && (s[total_length] == '\0'
		|| ft_strchr(VALID_TERMINATORS, s[total_length])))
		return (total_length);
	return (0);
}

int	is_int_triplet_strict(const char *s)
{
	int	total_length;
	int	length;
	int	values_found;
	int	passes;

	total_length = 0;
	values_found = 0;
	passes = 0;
	while (1)
	{
		passes++;
		length = is_int(&s[total_length]);
		if (length > 0)
			values_found++;
		total_length += length;
		if (passes == 3 || s[total_length++] != TRIPLET_DELIM)
			break ;
	}
	if (values_found == 3 && (s[total_length] == '\0'
		|| ft_strchr(VALID_TERMINATORS, s[total_length])))
		return (total_length);
	return (0);
}

// Value checking:
int	is_unitvec(t_vec v)
{
	return (feq(vec_length(v), 1.0));
}

int	is_fov(int i)
{
	return (0 <= i && i <= 180);
}

int	is_ratio(double d)
{
	return (fleq(0.0, d) && fleq(d, 1.0));
}