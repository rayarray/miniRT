/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_conversions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:55:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 20:30:54 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CONVERTERS_H
# define RT_CONVERTERS_H
# include "rt_typedef.h"
# include "element.h"
# include "libft.h"

// String conversions
t_element_type	rt_atoetype(const char *a);
double			rt_atof(const char *a);
t_vector		rt_atovec(const char *a);
t_color			rt_atocol(const char *a);
int				rt_atofov(const char *a);
t_vector		rt_atonorm(const char *a);
double			rt_atolight(const char *a);

#endif