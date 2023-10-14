/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_ambient_lighting.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:16 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 13:12:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ELEM_AMBIENT_LIGHTING_H
# define ELEM_AMBIENT_LIGHTING_H
# include "rt_typedef.h"
# include "element.h"

struct s_ambient_lighting
{
	struct s_element		base;
	double					lighting_ratio;
	t_color					color;
};

#endif