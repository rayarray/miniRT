/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 20:51:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# include <stdlib.h>
# include "rt_typedef.h"

typedef enum	e_element_type
{
	e_AMBIENT_LIGHTING = 0,
	e_CAMERA = 1,
	e_LIGHT = 2,
	e_SPHERE = 3,
	e_PLANE = 4,
	e_CYLINDER = 5,
	e_NAE = 6
}	t_element_type;

static const char	*valid_element_ids[7] = {"A", "C", "L", "sp", "pl", "cy", NULL};

#endif