/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validations.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:49:28 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/15 19:07:33 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VALIDATIONS_H
# define RT_VALIDATIONS_H
# define TRIPLET_DELIM ','
# include "rt_typedef.h"
# include "rt_math.h"
# include "libft.h"

// Form checks. Return number of characters traversed or 0 if not a valid input.
// Strict functions check that the string is null terminated after the value.
int	is_double(const char *s);
int	is_int(const char *s);
int	is_double_triplet_strict(const char *s);
int	is_int_triplet_strict(const char *s);

// Value checks
int	is_unitvec(t_vector v);
int	is_fov(int i);
int	is_ratio(double d);

#endif