/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_conversions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:55:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 22:00:40 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CONVERTERS_H
# define RT_CONVERTERS_H
# include "libft.h"
# include "rt_math.h"
# include "rt_typedef.h"
# include "element.h"

// String conversions
t_elem_type		rt_atoetype(const char *a);
double			rt_atof(const char *a);
t_vector		rt_atovec(const char *a);
t_color			rt_atocol(const char *a);

#endif