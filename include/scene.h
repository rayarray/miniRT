/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:18:59 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/08 22:44:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "element.h"
# include "vector.h"
# include "ray.h"
# include "camera.h"
# include "elem_ambient_lighting.h"
# include "light.h"

struct s_scene
{	// I would like to use explicitly struct members instead of typedef'd
	// members to make it clear that they are structs but maybe these are
	// handier to use.
	t_camera					camera;
	struct s_ambient_lighting	ambient;
	t_light				light;
	struct s_elem		**elems;
};

int	hitSphere(const t_vec center, double radius, const t_ray ray);

#endif	/* SCENE_H */