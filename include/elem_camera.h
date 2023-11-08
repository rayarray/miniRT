/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_camera.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:09:58 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 21:24:17 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEM_CAMERA_H
# define ELEM_CAMERA_H
# include "rt_typedef.h"
# include "element.h"

struct s_camera
{
	struct s_elem		base;
	t_vector				pos;
	t_vector				orientation;
	int						fov;
};

#endif