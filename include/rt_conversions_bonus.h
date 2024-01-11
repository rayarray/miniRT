/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_conversions_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:55:32 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CONVERSIONS_BONUS_H
# define RT_CONVERSIONS_BONUS_H
# include "libft.h"
# include "parser_bonus.h"
# include "rt_math_bonus.h"
# include "rt_typedef_bonus.h"

// String conversions
t_elem_type		rt_atoetype(const char *a);
double			rt_atof(const char *a);
t_vec			rt_atovec(const char *a);
t_color			rt_atocol(const char *a);

#endif