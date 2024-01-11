/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validations_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:49:28 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VALIDATIONS_BONUS_H
# define RT_VALIDATIONS_BONUS_H
# define TRIPLET_DELIM ','
# define VALID_TERMINATORS " \t"
# include "rt_typedef_bonus.h"
# include "rt_math_bonus.h"
# include "vector_bonus.h"
# include "libft.h"

// Form checks. Return number of characters traversed or 0 if not a valid input.
// Strict functions check that the string is null terminated after the value. It
// might be prudent to also accept values that end with whitespace and newlines.
int	is_double(const char *s);
int	is_int(const char *s);
int	is_byte(const char *s);
int	is_double_triplet_strict(const char *s);
int	is_byte_triplet_strict(const char *s);

// Checks that the components in the given vector are within [-1.0, 1,0] range
int	is_direction_vector(t_vec vec);

// Checks that the length of the vector is 1
int	is_unitvec(t_vec v);

// Checks that the given value is within [0, 180] range
int	is_fov(int i);

// Checks that the given value is within [0.0, 1.0] range
int	is_ratio(double d);

#endif