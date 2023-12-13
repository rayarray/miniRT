/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:02:19 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/13 16:40:49 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_validations.h"

// Value form checking
// These functions check if the given string represents a value of required type
int	is_double(const char *s)
{
	int	digit_found;
	int	len;

	digit_found = 0;
	len = 0;
	if (s[len] == '+' || s[len] == '-')
		len++;
	if (ft_isdigit(s[len]))
		digit_found = 1;
	while (ft_isdigit(s[len]))
		len++;
	if (s[len] == '.' && digit_found)
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

/*	// DEPRECATED
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
} */

int	is_byte(const char *s)
{
	int	len;
	int	val;

	if (!ft_isdigit(s[0]))
		return (0);
	len = is_int(s);
	if (len == 0 || len > 3)
		return (0);
	val = ft_atoi(s);
	if (val > 255 || val < 0)
		return 0;
	return (len);
}

int	is_byte_triplet_strict(const char *s)
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
		length = is_byte(&s[total_length]);
		if (length == 0)
			return (0);
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
