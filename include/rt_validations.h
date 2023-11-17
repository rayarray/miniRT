/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validations.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:49:28 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/18 01:02:03 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VALIDATIONS_H
# define RT_VALIDATIONS_H
# define TRIPLET_DELIM ','
# include "rt_typedef.h"
# include "rt_math.h"
# include "libft.h"

static const char	valid_terminators[4] = " \t\n";

// Form checks. Return number of characters traversed or 0 if not a valid input.
// Strict functions check that the string is null terminated after the value.
// (might be prudent to also accept values that end with whitespace and newlines)
int	is_double(const char *s);
int	is_int(const char *s);
int	is_double_triplet_strict(const char *s);
int	is_int_triplet_strict(const char *s);

// Checks that the components in the given vector are within [-1.0, 1,0] range
int	is_unitvec(t_vec v);

// Checks that the given value is within [0, 180] range
int	is_fov(int i);

// Checks that the given value is within [0.0, 1.0] range
int	is_ratio(double d);

#endif