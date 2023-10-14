/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_camera.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:58 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/14 13:12:12 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ELEM_CAMERA_H
# define ELEM_CAMERA_H
# include "rt_typedef.h"
# include "element.h"

struct s_camera
{
	struct s_element		base;
	t_vector				pos;
	t_vector				orientation;
	int						fov;
};

#endif