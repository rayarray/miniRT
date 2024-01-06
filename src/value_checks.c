/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:58:59 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/06 16:35:19 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_validations.h"

// Value checks. These check that the given value is within required range
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

int	is_direction_vector(t_vec vec)
{
	return ((fleq(fabs(vec.x), 1.0) && fleq(fabs(vec.y), 1.0)
			&& fleq(fabs(vec.z), 1.0))
		&& !(feq(vec.x, 0) && feq(vec.y, 0) && feq(vec.z, 0)));
}
