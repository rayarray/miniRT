/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:07:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 13:12:47 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ELEMENT_H
# define ELEMENT_H
# include <stdlib.h>

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

struct s_element
{
	t_element_type	type;
	// Insert vtable here with at least: constructor, destructor
};

static const struct s_element *(*element_ators[e_NAE])(const char **args);	// dynamic array?

#endif