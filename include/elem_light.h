/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_light.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:10:48 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 13:12:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ELEM_LIGHT_H
# define ELEM_LIGHT_
# include "rt_typedef.h"
# include "element.h"

struct s_light
{
	struct s_element		base;
	t_vector				pos;
	double					brightness;
	t_color					color;
};

#endif